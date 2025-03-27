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

    void Scene::Init()
    {
        std::cout << "Scene::Init() [IRenderable]\n";

        if (m_isInitialized) 
            return;      

        for (auto x : m_components)
            x->Init();

        m_isInitialized = true;
    }

    bool Scene::IsInitialized() const
    {
        return m_isInitialized;
    }

    void Scene::Render()
    {       
        std::cout << "Scene::Rendering..\n";

        for (auto x : m_components)
            x->Render();

        m_platform->TriggerPostRedisplay();
    }

    void Scene::AddComponent(Component* component)
    {
        m_components.emplace_back(component);
    }
}
