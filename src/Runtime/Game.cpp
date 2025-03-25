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
        std::cout << "Game::Constructor called\n";
    }

    Game::~Game() 
    {
        std::cout << "Game::Destructor called\n";

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
