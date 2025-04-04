/**
 *
 */

#pragma once

#include <functional>
#include <deque>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Types.hpp"
#include "Audio/AudioSystem.hpp"
#include "Audio/Volume.hpp"
#include "Scene/Scene.hpp"
#include "AssetManager/AssetManager.hpp"
#include "Runtime/Engine/VertexBuffer.hpp"
#include "Runtime/Engine/Backends/OpenGL/OpenGLVertexBuffer.hpp"

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

    class Component
    {
        public:
            Component() = default;
            virtual ~Component() = default;

        public:
            virtual void OnInit() = 0;
            virtual void OnUpdate() = 0;
            virtual void OnDestroy() = 0;
    };

    class QuadComponent final
        : public Component
    {
        public:
            QuadComponent() = delete;
            explicit QuadComponent(const std::vector<float>& vertices) : Component(), m_vertices(vertices) {};
            ~QuadComponent() override;

        public:
            void OnInit() override;
            void OnUpdate() override;
            void OnDestroy() override;

        private:
            GLuint m_shaderProgram{};
            std::vector<float> m_vertices;
            VertexBuffer* m_buffer{};
    };

    class AudioComponent final
        : public Component
          , public AudioSystem
    {
        public:
            explicit AudioComponent(std::string);
            ~AudioComponent() override;

        public:
            void OnInit() override;
            void OnUpdate() override;

        public:
            void TriggerPlayOnce();
            void TriggerPlayRepeat();

        public:
            void SetVolume(const Volume&) override;
            void OnDestroy() override;

        private:
            std::string m_filename;    
            bool m_repeats;
    };

    class TextComponent final : public Component
    {
        public:
            explicit TextComponent(const std::string& text);
            TextComponent(const std::string& text, float fontSize);
            TextComponent(const std::string& text, float fontSize, const Point& point);
            TextComponent(std::string  text, float fontSize, const Point& point, ColorAlpha color);
            ~TextComponent() override;
    
        public:
            [[nodiscard]] const std::string& GetText() const;
            void SetText(const std::string& text);
    
            [[nodiscard]] float GetFontSize() const;
            void SetFontSize(float fontSize);

            void OnInit() override;
            void OnUpdate() override;

        public:
            [[nodiscard]] Point GetPosition() const;
            void OnDestroy() override;

        private:
            std::string m_text;
            float m_fontSize;
            Point m_point;
            ColorAlpha m_colorAlpha;
    };

    class PositionComponent
        : public Component
    {
        public:
            explicit PositionComponent(float, float);
            void OnDestroy() override;
            [[nodiscard]] Point GetPoint() const;
        private:
            Point m_position;
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
            virtual void BeginFrame() = 0;
            virtual void EndFrame() = 0;
            virtual void RenderText(const TextComponent& component) = 0;
            virtual void RenderQuad(GLuint shaderProgram, GLuint VAO) = 0;
    };
 
    class OpenGLRenderer final : public IRenderer
    {
        public:
            OpenGLRenderer();
            ~OpenGLRenderer() override;
        public:
            void BeginFrame() override;
            void EndFrame() override;
            void RenderText(const TextComponent& component) override;
            void RenderQuad(GLuint shaderProgram, GLuint VAO) override;

        private:

    };

#ifdef NEON_BUILD_VULKAN
    // todo: create a Vulkan renderer
    //  class VulkanRenderer : public IRenderer
    //  {
    //     public:
    //         VulkanRenderer() = default;
    //         ~VulkanRenderer() = default;
    //  };
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
    };



    /********************************************
     *                                          *
     *          G A M E   E N G I N E           *
     *                                          *
     ********************************************/
    class GameEngine
    {
        public:
            GameEngine();
            ~GameEngine();

        public:
            bool Initialize(int width, int height, const char* title) const;
            void Run(Game* game) const;

            [[nodiscard]] Platform* GetPlatform() const;

            static VertexBuffer* CreateVertexBuffer(float* vertices, size_t size);

        private:
            Platform* m_platform;
    };

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

    class OpenGL final : public Platform
    {
        public:
            OpenGL();
            ~OpenGL() override;

            bool Initialize(int width, int height, const char* title) override;

            void Run(Game* game) override; 

            static GLuint CompileShader(const char* source, GLenum shaderType);
            static GLuint CreateShaderProgram(const char* vertexSource, const char* fragmentSource);

        protected:
            GLFWwindow* m_window;
            bool m_openGlInitialized = false;

            AssetManager* m_assetManager;
    };

    class GameEngineApi 
    {
        public:
            GameEngineApi(const GameEngineApi&) = delete;
            GameEngineApi& operator=(const GameEngineApi&) = delete;

        public:
            static GameEngineApi& getInstance();    
            static void RenderQuad(GLuint shaderProgram, GLuint VAO);
        
            [[nodiscard]] IRenderer* GetRenderer() const;

        private:
            GameEngineApi();
            ~GameEngineApi();

        private:
            IRenderer* m_renderer;
    };
}
 
