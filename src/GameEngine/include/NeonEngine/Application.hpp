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

#pragma once

#include <deque>

#include <NeonEngine/RuntimeBridge.hpp>
#include <NeonEngine/Scene.hpp>
#include <NeonEngine/YamlReader.hpp>
#include <NeonEngine/ScriptRegistry.hpp>

namespace Neon
{
    class Application
    {
        public:
            Application() = default;
            virtual ~Application();

            virtual std::vector<float> GetClearColor();
            virtual bool Initialize(WindowDimension width, WindowDimension height, const char* title);
            virtual void Run();

            void AddScene(Scene* scene);
            Scene* GetCurrentScene();

            ScriptRegistry& GetScriptRegistry();

            void SwitchScene();

            RuntimeBridge& GetBridge();

        protected:
            void SetSceneYaml(const std::string& sceneName);

        private:
            std::string GetSceneYaml() const;

        private:
            std::deque<Scene*> m_scenes;
            Scene* m_currentScene{nullptr};
            RuntimeBridge m_runtime;
            ScriptRegistry m_scriptRegistry;
            YamlReader m_yamlReader;
            std::string m_sceneYamlPath{};
            YScene m_sceneConfig;
            std::string m_rootPath{};
    };
}
