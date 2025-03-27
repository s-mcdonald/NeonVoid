/**
 * 
 */
#include <iostream>
#include <cmath>

#include "Runtime/Runtime.hpp"

namespace Neon
{
    Scene::Scene(Platform* platform) 
        : IRenderable()
        , m_platform(platform)
    {
        std::cout << "Scene::Constructor called\n";
    }

    Scene::~Scene() 
    {
        for (auto x : m_components)
            delete x;
        
        std::cout << "Scene::Destructor called\n";
    }

    void Scene::OnInit()
    {
        std::cout << "Scene::Init() [IRenderable]\n";

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
        std::cout << "Scene::Rendering..\n";

        for (auto x : m_components)
            x->OnUpdate();

        m_platform->TriggerPostRedisplay();
    }

    void Scene::AddComponent(Component* component)
    {
        m_components.emplace_back(component);
    }
}
