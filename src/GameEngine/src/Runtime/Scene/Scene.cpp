/**
 * 
 */
#include <iostream>
#include <cmath>

#include "Runtime/Runtime.hpp"

namespace Neon
{
    Scene::Scene(const SceneType type, Platform* platform)
        : IRenderable()
        , m_scene_type(type)
        , m_platform(platform)
    {
        #ifdef NEON_DEBUG
            std::cout << "Scene::Constructor called\n";
        #endif
    }

    Scene::~Scene() 
    {
        for (auto& [key, component] : m_components)
            delete component;
        
        #ifdef NEON_DEBUG
            std::cout << "Scene::Destructor called\n";
        #endif
    }

    void Scene::OnInit()
    {       
        if (m_isInitialized) 
            return;

        for (auto& [key, component] : m_components)
            component->OnInit();

        m_isInitialized = true;
    }

    bool Scene::IsInitialized() const
    {
        return m_isInitialized;
    }

    void Scene::OnUpdate()
    {       
        for (auto& [key, component] : m_components)
        {
            component->OnUpdate();
        }
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
}
