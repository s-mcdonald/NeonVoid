/**
 *
 */

#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <unordered_map>
#include <deque>

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

    /******************************************** 
     *                                          *
     *           C O M P O N E N T S            *
     *                                          *
     ********************************************/

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

    class TextComponent : public Component, public IRenderable
    {
        public:
            TextComponent(const std::string& text, int fontSize = 12);
            ~TextComponent();
    
        public:
            const std::string& GetText() const;
            void SetText(const std::string& text);
    
            int GetFontSize() const;
            void SetFontSize(int fontSize);

            void OnInit() override;
            void OnUpdate() override;
    
        private:
            std::string m_text;
            int m_fontSize;
    };

    /******************************************** 
     *                                          *
     *          A P I    R E N D E R E R        *
     *                                          *
     ********************************************/

     class IRenderer
     {
        public:
            virtual ~IRenderer() = default;
        public:
            virtual void RenderText(const TextComponent& component) = 0;
            virtual void RenderTriangle(float x1, float y1, float x2, float y2, float x3, float y3, const Color& color) = 0;
     };
 
     class OpenGLRenderer : public IRenderer
     {
        public:
            OpenGLRenderer();
            ~OpenGLRenderer() override;
        public:
            void RenderText(const TextComponent& component) override;
            void RenderTriangle(float x1, float y1, float x2, float y2, float x3, float y3, const Color& color);
     };

#ifdef NEON_BUILD_VULKAN
     class VulkanRenderer : public IRenderer
     {
        public:
            OpenGLRenderer() = default;
            ~OpenGLRenderer() = default;
        public:
            void RenderText(const TextComponent& component) override;
            void RenderTriangle(float x1, float y1, float x2, float y2, float x3, float y3, const Color& color);
     };
#endif

    /******************************************** 
     *                                          *
     *          G A M E - C O N T R O L         *
     *                                          *
     ********************************************/

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

        public:
            virtual IRenderer* GetRenderer() = 0;
            virtual void TriggerPostRedisplay() = 0;
    };

    class Scene : public IComponent, public IRenderable
    {
        public:
            Scene() = delete;
            Scene(SceneType type, Platform* platform);
            ~Scene();

        public:
            void OnInit() override;
            void OnUpdate() override;
            bool IsInitialized() const;

        public:
            void AddComponent(const std::string& tag, Component* component);
            Component* GetComponent(const std::string& tag);
            SceneType GetSceneType() const;

        private:
            SceneType m_scene_type;
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
            void SwitchScene();

        private:
            GameState* m_gameState{nullptr};
            std::deque<Scene*> m_scenes;
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

            IRenderer* GetRenderer() override;

        protected:
            void TriggerPostRedisplay() override;

        protected:
            GLFWwindow* m_window;
            bool m_openGlInitialized = false;
            IRenderer* m_renderer;
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
 
