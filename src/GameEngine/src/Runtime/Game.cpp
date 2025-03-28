/**
 * 
 */

#include <iostream>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    Game::Game()
        : m_gameState(new GameState())
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "Game::Constructor called\n";
        #endif
    }

    Game::~Game() 
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "Game::Destructor called\n";
        #endif

        for (auto s : m_scenes)
            delete s;

        delete m_gameState;
    }

    void Game::AddScene(Scene* scene)
    {
        m_scenes.emplace_back(scene);
    }

    Scene* Game::GetCurrentScene()
    {
        return m_scenes.at(0);
    }
}
