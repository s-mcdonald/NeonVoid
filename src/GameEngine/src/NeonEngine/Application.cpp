/**
 * {SourceHeader}
 */

#include <deque>

#include <fkYAML/node.hpp>
#include <NeonEngine/Application.hpp>

namespace Neon 
{
    Application::~Application()
    {
        for (const auto s : m_scenes)
        {
            delete s;
        }
    }

    bool Application::Initialize(const WindowDimension width, const WindowDimension height, const char* title)
    {
        if (m_runtime.Initialize(width, height, title))
        {
            m_yamlReader.Read("/home/sam/Game/Neon/build/assets/game.yaml");

            m_yamlReader.Init();

            return true;
        }

        return false;
    }

    void Application::Run()
    {
        m_runtime.Run(this);
    }

    void Application::AddScene(Scene* scene)
    {
        m_scenes.push_back(scene);
    }

    Scene* Application::GetCurrentScene()
    {
        if (m_currentScene == nullptr)
        {
            SwitchScene();
        }

        return m_currentScene;
    }

    void Application::SwitchScene()
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

        // we must have reached the end of the Application..
        // if (m_scenes.empty())....
    }
}
