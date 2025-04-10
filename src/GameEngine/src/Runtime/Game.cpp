/**
 *
 */

#include <deque>

#include <Runtime/Runtime.hpp>
#include <Runtime/Game.hpp>

namespace Neon 
{
    Game::~Game()
    {
        for (const auto s : m_scenes)
        {
            delete s;
        }
    }

    bool Game::Initialize(const int width, const int height, const char* title) const
    {
        return m_gameEngine.Initialize(width, height, title);
    }

    void Game::Run()
    {
        m_gameEngine.Run(this);
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
        if (m_currentScene == nullptr && !m_scenes.empty())
        {
            m_currentScene = m_scenes.front();
            m_scenes.pop_front();
            return;
        }

        if (m_currentScene != nullptr && !m_scenes.empty())
        {
            m_currentScene->Destroy();

            m_currentScene = m_scenes.front();
            m_scenes.pop_front();
            return;
        }

        // we must have reached the end of the game..
        // if (m_scenes.empty())....
    }
}
