/**
 * 
 */
#include <iostream>

#include "Game.h"
#include "Game/Scene.h"

namespace Neon 
{
    Game::Game()
    {
        std::cout << "Game::Constructor called\n";
    }

    Game::~Game() 
    {
        std::cout << "Game::Destructor called\n";
        delete m_onlyScene;
    }

    void Game::AddScene(Scene* scene)
    {
        m_onlyScene = scene;
    }
}
