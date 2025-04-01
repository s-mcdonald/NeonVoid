/**
 *
 */

#include <iostream>
#include <deque>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    Game::Game()
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
    }

    void Game::AddScene(Scene* scene)
    {
        m_scenes.push_back(scene);
    }

    Scene* Game::GetCurrentScene()
    {
        if (m_currentScene == nullptr)
        {
            SwitchScene();
        }

        return m_currentScene;
    }

    void Game::SwitchScene()
    {
        if (!m_scenes.empty())
        {
            m_currentScene = m_scenes.front();
            m_scenes.pop_front();
        }
    }
}
