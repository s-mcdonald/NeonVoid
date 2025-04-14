/**
 * {SourceHeader}
 */

#pragma once

#include <Runtime/GameEngine.hpp>
#include <Runtime/Scene/Scene.hpp>

namespace Neon
{
    class Application
    {
        public:
            Application() = default;
            virtual ~Application();

        public:
            virtual bool Initialize(WindowDimension width, WindowDimension height, const char* title) const;
            virtual void Run();

        public:
            void AddScene(Scene* scene);
            Scene* GetCurrentScene();
            void SwitchScene();

        private:
            std::deque<Scene*> m_scenes;
            Scene* m_currentScene{nullptr};

        private:
            GameEngine m_gameEngine;
    };
}