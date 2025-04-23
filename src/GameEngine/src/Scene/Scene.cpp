/**
 *    ███╗   ██╗███████╗ ██████╗ ███╗   ██╗
 *    ████╗  ██║██╔════╝██╔═══██╗████╗  ██║
 *    ██╔██╗ ██║█████╗  ██║   ██║██╔██╗ ██║
 *    ██║╚██╗██║██╔══╝  ██║   ██║██║╚██╗██║
 *    ██║ ╚████║███████╗╚██████╔╝██║ ╚████║
 *    ╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═══╝
 * ========================================
 *                 NeonVoid
 *         A 2D Game Engine in C++
 * ----------------------------------------
 * License: MIT
 * Copyright (c) : 2024 Sam McDonald
 * Repository: https://github.com/s-mcdonald/NeonVoid
 */

#include <NeonEngine/Types.hpp>
#include <NeonEngine/ComponentLoader.hpp>
#include <NeonEngine/Scene.hpp>
#include <NeonEngine/Application.hpp>

namespace Neon
{
    Scene::Scene(Application* app, const YScene config)
        : mx_app(app)
        , m_sceneConfig(config)
    {
        m_nextEntityID = START_NEXT_ENTITY_ID;
    }

    Scene::~Scene()
    {
        Destroy();

        m_sceneConfig.components.clear();
        m_sceneConfig.components.shrink_to_fit();
        m_sceneConfig.entities.clear();
        m_sceneConfig.entities.shrink_to_fit();
    }

    bool Scene::IsInitialized() const
    {
        return m_isInitialized;
    }

    void Scene::Init()
    {
        if (m_isInitialized)
        {
            return;
        }

        // Scene components must be initialized before entity components
        InitRenderable(m_components);
        InitRenderable(m_entities);

        m_isInitialized = true;
    }

    void Scene::Update()
    {
        // check for collision prior to other updates
        m_collisionSystem.OnUpdate();

        // Scene components must be updated before entity components
        UpdateRenderable(m_components);
        UpdateRenderable(m_entities);
    }

    void Scene::Render()
    {
        // Scene components must be rendered before entity components
        RenderRenderable(m_components);
        RenderRenderable(m_entities);
    }

    void Scene::Destroy()
    {
        // Reverse the order for destruction
        DestroyRenderable(m_entities);
        DestroyRenderable(m_components);
    }

    void Scene::HandleInput(Input* input)
    {
        HandlesInput(m_entities, input);
    }

    void Scene::AddEntity(const EntityID id, Entity* entity)
    {
        m_entities[id] = entity;
    }

    void Scene::AddComponent(const std::string& tag, Component* component)
    {
        // what do we do if it already exists?
        m_components[tag] = component;
    }

    Component* Scene::GetComponent(const std::string& tag)
    {
        if (auto it = m_components.find(tag); it != m_components.end())
        {
            auto& [key, component] = *it;

            return component;
        }

        return nullptr;
    }

    Entity* Scene::GetEntity(const EntityID id) const
    {
        if (auto it = m_entities.find(id); it != m_entities.end())
        {
            auto& [key, entity] = *it;

            return entity;
        }

        return nullptr;
    }

    Entity* Scene::GetPlayerEntity() const
    {
        return GetEntity(MAIN_PLAYER_ENTITY_ID);
    }

    SceneType Scene::GetSceneType() const
    {
        return m_sceneConfig.sceneType;
    }

    bool Scene::MakeComponent(const std::string& compoTag)
    {
        for (auto& c : m_sceneConfig.components)
        {
            if (c.name == compoTag)
            {
                auto* realComponent = ComponentLoader::MakeComponentReal(c, *mx_app);
                realComponent->SetScene(this);
                AddComponent(compoTag, realComponent);
                return true;
            }
        }

        return false;
    }

    Entity* Scene::MakeEntity(const std::string& entityTag)
    {
        for (auto entity : m_sceneConfig.entities)
        {
            if (entity.name == entityTag)
            {
                auto* e = new Entity(++m_nextEntityID);

                auto components = ComponentLoader::CollectComponents(entity.components, *mx_app);

                for (auto& [c_type, comp] : components)
                {
                     comp->SetScene(this);
                     e->AddComponent(comp);

                     if (c_type == "collision")
                     {
                         m_collisionSystem.RegisterEntity(e);
                     }
                }
                AddEntity(e->GetId(), e);
                return e;
            }
        }

        throw std::runtime_error("Entity not found");
    }

    template <typename T>
    void Scene::InitRenderable(const T& t)
    {
        for (auto& [key, value] : t)
        {
            value->OnInit();
        }
    }

    template <typename T>
    void Scene::UpdateRenderable(const T& t)
    {
        for (auto& [key, value] : t)
        {
            value->OnUpdate();
        }
    }

    template <typename T>
    void Scene::RenderRenderable(const T& t)
    {
        for (auto& [key, value] : t)
        {
            value->OnRender();
        }
    }

    template <typename T>
    void Scene::DestroyRenderable(const T& t)
    {
        for (auto& [key, value] : t)
        {
            value->OnDestroy();

            delete value;
        }
    }

    template <typename T>
    void Scene::HandlesInput(const T& t, Input* input)
    {
        for (auto& [key, value] : t)
        {
            value->HandleInput(input);
        }
    }
}
