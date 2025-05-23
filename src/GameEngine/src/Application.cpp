/**
 *    ███╗   ██╗███████╗ ██████╗ ███╗   ██╗
 *    ████╗  ██║██╔════╝██╔═══██╗████╗  ██║
 *    ██╔██╗ ██║█████╗  ██║   ██║██╔██╗ ██║
 *    ██║╚██╗██║██╔══╝  ██║   ██║██║╚██╗██║
 *    ██║ ╚████║███████╗╚██████╔╝██║ ╚████║
 *    ╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═══╝
 * ========================================
 *                 NeonVoid
 *         A 2D Game Engine in C++
 * ----------------------------------------
 * License: MIT
 * Copyright (c) : 2024 Sam McDonald
 * Repository: https://github.com/s-mcdonald/NeonVoid
 */

#include <deque>
#include <filesystem>
#include <iostream>

#include <fkYAML/node.hpp>

#include <NeonEngine/Types.hpp>
#include <NeonEngine/ComponentLoader.hpp>
#include <NeonEngine/Application.hpp>

namespace Neon 
{
    Application::~Application()
    {
        for (const auto s : m_scenes)
        {
            delete s;
        }

        auto cleanupComponent = [](YComponent& comp)
        {
            switch(comp.configType)
            {
                case ConfigType::Shader:
                    delete comp.shaderConfig;
                    break;
                case ConfigType::Audio:
                    delete comp.audioConfig;
                    break;
                case ConfigType::Position:
                    delete comp.posConfig;
                    break;
                case ConfigType::None:
                case ConfigType::Script:
                case ConfigType::Text:
                case ConfigType::Movement:
                    break;
            }
        };

        for (auto& comp : m_sceneConfig.components)
        {
            cleanupComponent(comp);
        }

        for (auto& entity : m_sceneConfig.entities)
        {
            for (auto& comp : entity.components)
            {
                cleanupComponent(comp);
            }
        }

        if (m_currentScene)
        {
            m_currentScene = nullptr;
        }
    }

    bool Application::Initialize(const WindowDimension width, const WindowDimension height, const char* title)
    {
        m_rootPath = std::filesystem::current_path().string();

        if (false == m_runtime.Initialize(width, height, title))
        {
            return false;
        }

        m_yamlReader.Read(m_sceneYamlPath);

        // @todo: we need to validate this data
        m_sceneConfig = m_yamlReader.Init();

        auto* scene = new Scene(this, m_sceneConfig);

        if (false == m_sceneConfig.fonts.path.empty())
        {
            RuntimeApi::GetInstance().GetRenderer()->LoadFont(m_sceneConfig.fonts.path);
        }

        std::unordered_map<std::string, Component*> scriptsForScene  = ComponentLoader::CollectComponents(m_sceneConfig.scripts, *this);

        for (auto& [name, comp] : scriptsForScene)
        {
            comp->SetScene(scene);
            scene->AddComponent(name, comp);
        }

        AddScene(scene);

        return true;
    }

    void Application::Run()
    {
        m_runtime.Run(this);
    }

    void Application::SetSceneYaml(const std::string& sceneName)
    {
        m_sceneYamlPath = sceneName;
    }

    RuntimeBridge& Application::GetBridge()
    {
        return m_runtime;
    }

    ScriptRegistry& Application::GetScriptRegistry()
    {
        return m_scriptRegistry;
    }

    std::string Application::GetSceneYaml() const
    {
        return m_sceneYamlPath;
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

        // we must have reached the end of the Application.
        // if (m_scenes.empty())....
    }

    std::vector<float> Application::GetClearColor()
    {
        return {
            0.0f, 0.0f, 0.0f, 0.0f
        };
    };
}
