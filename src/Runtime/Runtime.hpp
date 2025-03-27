/**
 *
 */

#pragma once

#include <iostream>
#include <functional>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <miniaudio.h>

namespace Neon 
{
    class Game;

    using InitFunction = std::function<void()>;
    using RenderFunction = std::function<void()>;

    class IRenderable
    {
        public:
            virtual ~IRenderable() = default;
            virtual void Init() = 0;
            virtual void Render() = 0;
    };

    class Component : public IRenderable
    {
        public:
            Component();
            virtual ~Component();
        public:
            virtual void Init() override;
            virtual void Render() override;

            void SetInitFunction(InitFunction initFunc);
            void SetRenderFunction(RenderFunction renderFunc);

        // ya ya.. only temp until I sort out the assignment for the lambda
        public:
            GLuint m_VAO;
            GLuint m_VBO;
            GLuint m_shaderProgram;
        private:
            InitFunction m_initFunc;
            RenderFunction m_renderFunc;
    };

    // More Component Types here .. TextComponent ect..
    // class TextComponent : public Component;
    // class Player : public Component;

    class AudioSystem 
    {
        public:
            AudioSystem();
            ~AudioSystem();

        public:
            void Play(const std::string& filename);
            void Stop();

        private:
            ma_device_config getDeviceConfig();
            static void dataCallback(ma_device* pDevice, void* pOutput, const void* pInput, uint32_t frameCount);

        private:
            ma_decoder m_decoder;
            ma_device m_device;
            bool m_isPlaying{false};            
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
    };

    class Scene : public IRenderable
    {
        public:
            Scene() = delete;
            Scene(Platform* platform);
            ~Scene();

        // OpenGL Hooks
        public:
            void Init() override;
            void Render() override;
            bool IsInitialized() const;

        // Component Management
        public:
            void AddComponent(Component* component);

        // Members.. ;)
        private:
            Neon::Platform* m_platform{nullptr};
            bool m_isInitialized = false;
            std::vector<Component*> m_components;
    };

    // define more scenes here... TitleScene ect

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
            std::vector<Scene*> m_scenes;
    };

    class OpenGL : public Platform
    {
        public:
            OpenGL();
            ~OpenGL();

            bool Initialize(int width, int height, const char* title) override;

            void Run(Game* game) override; 

            static GLuint CompileShader(const char* source, GLenum shaderType);
            static GLuint CreateShaderProgram(const char* vertexSource, const char* fragmentSource);

        protected:
            void TriggerPostRedisplay() override;

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

        private:
            Platform* m_platform;
    };
}
 
