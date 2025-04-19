/**
 * {SourceHeader}
 */

#pragma once

#include <deque>

#include <NeonEngine/RuntimeBridge.hpp>
#include <NeonEngine/Scene.hpp>
#include <NeonEngine/YamlReader.hpp>

namespace Neon
{
    class Application
    {
        public:
            Application() = default;
            virtual ~Application();

        public:
            virtual bool Initialize(WindowDimension width, WindowDimension height, const char* title);
            virtual void Run();

        public:
            void AddScene(Scene* scene);
            Scene* GetCurrentScene();
            void SwitchScene();

        protected:
            void SetSceneYaml(const std::string& sceneName);
            static std::unordered_map<std::string, Component*> CollectComponents(std::vector<YComponent> components);

        private:
            std::string GetSceneYaml() const;

        private:
            std::deque<Scene*> m_scenes;
            Scene* m_currentScene{nullptr};

        private:
            RuntimeBridge m_runtime;
            YamlReader m_yamlReader;
            std::string m_sceneYamlPath{};
            YScene m_sceneConfig;
    };
}