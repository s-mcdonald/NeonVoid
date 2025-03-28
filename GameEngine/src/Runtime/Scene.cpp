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
        for (auto x : m_components)
            delete x;
        
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

        for (auto x : m_components)
            x->OnInit();

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

        for (auto x : m_components)
            x->OnUpdate();

        m_platform->TriggerPostRedisplay();

        // hmm do we check for user input here
        // CheckUserInputControls();
        // CheckUserSpecialInputControls();
        // CheckUserMouseControls();
    }

    void Scene::AddComponent(Component* component)
    {
        m_components.emplace_back(component);
    }
}
