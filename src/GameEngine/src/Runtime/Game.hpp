
#pragma once

namespace Neon
{
    class Scene;

    class Game
    {
        public:
            Game() = default;
            virtual ~Game();

        public:
            virtual bool Initialize(int width, int height, const char* title) const;
            virtual void Run();

        public:
            void AddScene(Scene* scene);
            Scene* GetCurrentScene();
            void SwitchScene();

        private:
            std::deque<Scene*> m_scenes;
            Scene* m_currentScene{nullptr};

        private:
            GameEngine gameEngine;
    };
}