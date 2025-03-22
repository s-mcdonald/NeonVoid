/**
 * 
 */
#include <iostream>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    Scene::Scene(Platform* platform) : m_platform(platform)
    {
        std::cout << "Scene::Constructor called\n";
    }

    Scene::~Scene() 
    {
        std::cout << "Scene::Destructor called\n";
    }

    void Scene::Render() const
    {       
        std::cout << "Scene::Renderrrring..\n";

        // In order for text or ui to be drawn from Scene, we will need access to the Platform.
        // Platform.RenderText("Some text", position, shader);

        // Call platform independant action
        m_platform->TriggerPostRedisplay();

        std::cout << "Scene::Post Trigger..\n";
    }
}
