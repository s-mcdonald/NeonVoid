/**
 * 
 */

#include <iostream>
#include <deque>

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
        m_scenes.push_back(scene);
    }

    Scene* Game::GetCurrentScene()
    {
        return m_scenes.empty() ? nullptr : m_scenes.front();
    }

    // @todo:
    // we need to be able to remove the OnINit() call from the main game loop
    // and trigger this switch scene func.
    // so far this func does not get called.
    void Game::SwitchScene()
    {
        if (!m_scenes.empty())
        {
            Scene* currentScene = m_scenes.front();
            m_scenes.pop_front();

            if (false == currentScene->IsInitialized())
            {
                currentScene->OnInit();
                std::cout << "Scene initialized in run loop\n";
            }
        }
    }
}
