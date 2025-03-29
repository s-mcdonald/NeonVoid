/**
 *
 */

#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <miniaudio.h>

#include "Types.hpp"
#include "Audio/Volume.hpp"

namespace Neon 
{
    class Game;

    class AudioSystem 
    {
        public:
            AudioSystem();
            ~AudioSystem();

        public:
            virtual void Play(const std::string& filename);
            virtual void PlayOnce(const std::string& filename);
            virtual void PlayOnLoop(const std::string& filename);
            virtual void Stop();
            virtual void Update();

            void SetVolume(const Volume& volume);

        private:
            ma_device_config getDeviceConfig();
            static void dataCallback(ma_device* pDevice, void* pOutput, const void* pInput, uint32_t frameCount);

        private:
            ma_decoder m_decoder;
            ma_device m_device;
            bool m_isPlaying{false};
            bool m_onLoop{false};
            bool m_isStopRequested{false};
    };

    using InitFunction = std::function<void()>;
    using RenderFunction = std::function<void()>;

    class IRenderable
    {
        //
    };

    class IComponent
    {
        public:
            virtual ~IComponent() = default;
            virtual void OnInit() = 0;
            virtual void OnUpdate() = 0;
    };

    class Component : public IComponent
    {
        public:
            Component();
            virtual ~Component();
        public:
            virtual void OnInit() override;
            virtual void OnUpdate() override;

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

    class AudioComponent 
        : public Component
        , public AudioSystem
    {
        public:
            AudioComponent(const std::string& filename);
            ~AudioComponent();

        public:
            void OnInit();
            void OnUpdate();

        public:
            void TriggerPlayOnce();
            void TriggerPlayRepeat();

        public:
            void SetVolume(const Volume& volume);

        private:
            std::string m_filename;    
            bool m_repeats;
    };

    class GameState
    {
        public:
            GameState();
            ~GameState();
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

    class Scene : public IComponent, public IRenderable
    {
        public:
            Scene() = delete;
            Scene(Platform* platform);
            ~Scene();

        // OpenGL Hooks
        public:
            void OnInit() override;
            void OnUpdate() override;
            bool IsInitialized() const;

        // Component Management
        public:
            void AddComponent(const std::string& tag, Component* component);
            Component* GetComponent(const std::string& tag);

        // Members.. ;)
        private:
            Neon::Platform* m_platform{nullptr};
            bool m_isInitialized = false;
            std::unordered_map<std::string, Component*> m_components;
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
 
