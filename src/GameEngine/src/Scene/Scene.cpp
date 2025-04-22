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
        MakeAll();
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

        OnInit();

        m_isInitialized = true;
    }

    void Scene::Update()
    {
        // check for collision prior to other updates
        m_collisionSystem.OnUpdate();

        // Scene components must be updated before entity components
        UpdateRenderable(m_components);
        UpdateRenderable(m_entities);

        OnUpdate();
    }

    void Scene::Render()
    {
        // Scene components must be rendered before entity components
        RenderRenderable(m_components);
        RenderRenderable(m_entities);

        OnRender();
    }

    void Scene::Destroy()
    {
        // Reverse the order for destruction
        DestroyRenderable(m_entities);
        DestroyRenderable(m_components);

        OnDestroy();
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

    // Dynamically makes an entity and adds to the current gameplay/scene.
    Entity* Scene::MakeEntity(const YEntity& yentity)
    {
        auto* e = new Entity(++m_nextEntityID);

        AddEntity(e->GetId(), e);

        return e;
    }

    void Scene::MakeAll()
    {
        for (auto& entity : m_sceneConfig.entities)
        {
            std::unordered_map<std::string, Component*> componentsForEntity = ComponentLoader::CollectComponents(entity.components, mx_app->GetBridge());

            EntityID entityId = (entity.type == EntityType::Player) ? MAIN_PLAYER_ENTITY_ID : ++m_nextEntityID;

            auto* entityToAdd = new Entity(entityId);
            for (auto& [c_type, comp] : componentsForEntity)
            {
                // redundant code, need to refactor, @see application comp->SetScene(scene);
                comp->SetScene(this);
                entityToAdd->AddComponent(comp);

                if (c_type == "collision")
                {
                    m_collisionSystem.RegisterEntity(entityToAdd);
                }
            }

            AddEntity(entityToAdd->GetId(), entityToAdd);
        }
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
