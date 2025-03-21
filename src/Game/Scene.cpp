/**
 * 
 */
#include <iostream>

#include "Game/Scene.h"

namespace Neon 
{
    Scene::Scene()
    {
        std::cout << "Scene::Constructor called\n";
    }

    Scene::~Scene() 
    {
        std::cout << "Scene::Destructor called\n";
    }
}
