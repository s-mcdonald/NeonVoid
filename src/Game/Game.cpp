/**
 * 
 */
#include <iostream>

#include "Game.h"
#include "Game/Scene.h"

namespace Neon 
{
    Game::Game()
        : m_gameState(new GameState())
    {
        std::cout << "Game::Constructor called\n";
    }

    Game::~Game() 
    {
        std::cout << "Game::Destructor called\n";
        delete m_onlyScene;
        delete m_gameState;
    }

    void Game::AddScene(Scene* scene)
    {
        m_onlyScene = scene;
    }

    Scene* Game::GetCurrentScene()
    {
        return m_onlyScene;
    }
}
