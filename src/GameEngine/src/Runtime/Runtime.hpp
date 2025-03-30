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

#include "stb_truetype.h"

#include "Types.hpp"

#include "Audio/AudioSystem.hpp"
#include "Audio/Volume.hpp"
#include "Entity/Entity.hpp"

namespace Neon 
{
    class Game;

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
            TextComponent(const std::string& text, int fontSize, const Point& point);
            ~TextComponent();
    
        public:
            const std::string& GetText() const;
            void SetText(const std::string& text);
    
            int GetFontSize() const;
            void SetFontSize(int fontSize);

            void OnInit() override;
            void OnUpdate() override;

        public:
            Point GetPosition();
    
        private:
            std::string m_text;
            int m_fontSize;
            Point m_point;
    };

    class PositionComponent : public Component 
    {
        public:
            PositionComponent(float x = 0.0f, float y = 0.0f) : X(x), Y(y) {}
        
            // we should prob use Point for this
            float X, Y;
    };

    class ComponentManager 
    {
        public:
            template <typename T>
            void AddComponent(Entity& entity, T* component);
        
            template <typename T>
            T* GetComponent(const Entity& entity);
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
            void LoadFont(const char* fontPath);
            void RenderText([[ maybe_unused ]] const TextComponent& component) override;
            void RenderText(const std::string& text, float x, float y, int fontSize);
            void RenderTriangle(
                [[ maybe_unused ]] float x1, 
                [[ maybe_unused ]] float y1, 
                [[ maybe_unused ]] float x2, 
                [[ maybe_unused ]] float y2, 
                [[ maybe_unused ]] float x3, 
                [[ maybe_unused ]] float y3, 
                [[ maybe_unused ]] const Color& color
            );

            GLuint createTextureFromBitmap(unsigned char* bitmap, int width, int height);
        private:
            stbtt_fontinfo m_font;
            unsigned char* m_fontBuffer;
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
 
