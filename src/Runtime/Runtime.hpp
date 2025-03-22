/**
 *
 */

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
 
namespace Neon 
{
    class Game;

    class GameState
    {
        public:
            GameState();
            ~GameState();
        
        public:
            bool IsLoading();                   // Query these as much as you want
            bool IsMenuScene();                 // Query these as much as you want
            bool IsGamePlayScene();             // Query these as much as you want
            
            void LoadLoading();                 // The load command will immediately load the new scene/menu or whatever, if you
            void LoadMenuScene();               // call the same Scene, it should not reload it.
            void LoadGamePlayScene(int level);
    };

    class Platform 
    {
        public:
            Platform();
            virtual ~Platform();
    
            virtual bool Initialize(int width, int height, const char* title);

            virtual void Run(Game* game);

            virtual void TriggerPostRedisplay();
            
        protected:
            virtual void CleanResources();
    };

    class Scene
    {
        public:
            Scene() = default;
            Scene(Platform* platform);
            ~Scene();

        public:
            void Render() const;
        private:
            Neon::Platform* m_platform{nullptr};
    };

    class Game
    {
        public:
            Game();
            ~Game();

        public:
            void AddScene(Scene* scene);

            Scene* GetCurrentScene();

        private:
            GameState* m_gameState{nullptr};    
            Scene* m_onlyScene;
    };

    class OpenGL : public Platform
    {
        public:
            OpenGL();
            ~OpenGL();

            bool Initialize(int width, int height, const char* title) override;

            void Run(Game* game) override; 

        protected:
            void LoadFont(const char *fontPath);
            void CompileShaders();
            void RenderText(const char *text, float x, float y, float scale, glm::vec3 color);


            void TriggerPostRedisplay() override;
            void CleanResources() override;

        protected:
            GLFWwindow* m_window;
    };

    class GameEngine
    {
        public:
            GameEngine();
            ~GameEngine();

        public:
            bool Initialize(int width, int height, const char* title);

            void Run(Game* game);
            
            Platform* GetPlatform() const;

        protected:            
            void CleanResources();

        private:
            Platform* m_platform;
    };

}
 
