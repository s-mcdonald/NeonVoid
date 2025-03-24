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
        std::cout << "Scene::Destructor called\n";

        if (m_component) delete m_component;
    }

    void Scene::Init()
    {
        std::cout << "Scene::Init() [IRenderable]\n";

        if (m_isInitialized) return;      

        if (m_component) m_component->Init();

        m_isInitialized = true;
    }

    bool Scene::IsInitialized() const
    {
        return m_isInitialized;
    }

    void Scene::Render()
    {       
        std::cout << "Scene::Rendering..\n";

        if (m_component) m_component->Render();

        m_platform->TriggerPostRedisplay();
    }

    // Eventually we can add abunch of components to a scene.
    // for now we just need to prove a render from a cmp.
    void Scene::AddComponent(Component* component)
    {
        m_component = component;
    }
}
