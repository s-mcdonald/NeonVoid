/**
 * 
 */
#include <iostream>
#include <cmath>

#include "Runtime/Runtime.hpp"

namespace Neon
{
    Scene::Scene(Platform* platform) 
        : IComponent()
        , IRenderable()
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
        #ifdef NEON_DEBUG
            std::cout << "Scene::Init()\n";
        #endif
        
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
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "Scene::Rendering..\n";
        #endif

        for (auto& [key, component] : m_components)
            component->OnUpdate();

        m_platform->TriggerPostRedisplay();
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
}
