/**
 * 
 */
#include <iostream>
#include <cmath>

#include "Runtime/Types.hpp"
#include "Runtime/Scene/Scene.hpp"

namespace Neon
{
    Scene::Scene(const SceneType type)
        : m_scene_type(type)
    {
        #ifdef NEON_DEBUG
            std::cout << "Scene::Constructor called\n";
        #endif
    }

    Scene::~Scene() 
    {
        #ifdef NEON_DEBUG
            std::cout << "Scene::Destructor called\n";
        #endif

        Destroy();
    }

    void Scene::Destroy()
    {
        DestroyRenderable(m_entities);
        DestroyRenderable(m_components);

        OnDestroy();
    }

    bool Scene::IsInitialized() const
    {
        return m_isInitialized;
    }

    void Scene::Init()
    {
        if (m_isInitialized)
            return;

        InitRenderable(m_entities);
        InitRenderable(m_components);

        OnInit();

        m_isInitialized = true;
    }

    void Scene::Update()
    {       
        UpdateRenderable(m_entities);
        UpdateRenderable(m_components);
        OnUpdate();
    }

    void Scene::AddComponent(const std::string& tag, Component* component)
    {
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

    SceneType Scene::GetSceneType() const
    {
        return m_scene_type;
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
    void Scene::DestroyRenderable(const T& t)
    {
        for (auto& [key, value] : t)
        {
            value->OnDestroy();

            delete value;
        }
    }

}
