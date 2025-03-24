/**
 *
 */

#pragma once

#include <iostream>
#include <miniaudio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
 
namespace Neon 
{
    class Game;

    class IRenderable 
    {
        public:
            virtual void Init() = 0;
            virtual void Render() = 0;
    };

    class AudioSystem 
    {
        public:
            AudioSystem();
            ~AudioSystem();

        private:
    };

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
            Platform() = default;
            virtual ~Platform() = default;
        public:
            virtual bool Initialize(int width, int height, const char* title) = 0;
            virtual void Run(Game* game) = 0;
            virtual void TriggerPostRedisplay() = 0;

            virtual GLuint compileShader(const char* source, GLenum shaderType) = 0;
            virtual GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource) = 0;
            
        protected:
            virtual void CleanResources() = 0;
    };

    class Scene : public IRenderable
    {
        public:
            Scene() = delete;
            Scene(Platform* platform);
            ~Scene();

        public:
            void Init() override;
            void Render() override;
            bool IsInitialized() const;

        private:
            Neon::Platform* m_platform{nullptr};
            GLuint VAO; 
            GLuint VBO;
            GLuint shaderProgram;
            bool m_isInitialized = false;
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

            GLuint compileShader(const char* source, GLenum shaderType) override;
            GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource) override;

        protected:
            void TriggerPostRedisplay() override;
            void CleanResources() override;

        protected:
            GLFWwindow* m_window;
            bool m_openGlInitialized = false;
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
 
