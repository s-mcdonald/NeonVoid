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

        m_entities.clear();
        m_components.clear();

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
        m_collisionSystem.OnUpdate();

        // Scene components must be updated before entity components
        UpdateRenderable(m_components);
        UpdateRenderable(m_entities);

        ProcessPendingDeletions();
    }

    void Scene::Render()
    {
        // Scene components must be rendered before entity components
        RenderRenderable(m_components);
        RenderRenderable(m_entities);
    }

    void Scene::Destroy()
    {
        DestroyRenderable(m_entities);
        DestroyRenderable(m_components);
    }

    void Scene::HandleInput(Input* input)
    {
        HandlesInput(m_entities, input);
    }

    void Scene::AddEntity(const EntityID id, Entity* entity)
    {
        auto it = m_entities.find(id);

        if (it != m_entities.end())
        {
            it->second->OnDestroy();
            delete it->second;
        }
        m_entities[id] = entity;
    }

    void Scene::AddComponent(const std::string& tag, Component* component)
    {
        auto it = m_components.find(tag);
        if (it != m_components.end())
        {
            delete it->second;
            it->second = component;
        }
        else
        {
            m_components[tag] = component;
        }
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

    void Scene::DestroyEntity(const EntityID id)
    {
        auto it = m_entities.find(id);
        if (it != m_entities.end())
        {
            m_pendingDeletions.push_back(id);
        }
    }

    void Scene::DestroyEntity(const Entity* entity)
    {
        if (entity != nullptr)
        {
            DestroyEntity(entity->GetId());
        }
    }

    void Scene::ProcessPendingDeletions()
    {
        for (const auto id : m_pendingDeletions)
        {
            auto it = m_entities.find(id);
            if (it != m_entities.end())
            {
                Entity* entity = it->second;

                if (entity != nullptr)
                {
                    entity->OnDestroy();
                    m_collisionSystem.DeregisterEntity(entity);
                    delete entity;
                }

                m_entities.erase(it);
            }
        }
        m_pendingDeletions.clear();
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
                Entity* e = nullptr;

                try
                {
                    e = new Entity(++m_nextEntityID, entity.name, entity.type, this);

                    auto components = ComponentLoader::CollectComponents(entity.components, *mx_app);

                    for (auto& [c_type, comp] : components)
                    {
                        comp->SetScene(this);
                        e->AddComponent(comp);

                        if (comp->GetType() == "collision")
                        {
                            m_collisionSystem.RegisterEntity(e);
                        }
                    }
                    AddEntity(e->GetId(), e);
                    return e;
                }
                catch (...)
                {
                    delete e;
                    throw;
                }
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
    void Scene::DestroyRenderable(T& t)
    {
        for (auto& [key, value] : t)
        {
            value->OnDestroy();

            delete value;
        }

        t.clear();
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
