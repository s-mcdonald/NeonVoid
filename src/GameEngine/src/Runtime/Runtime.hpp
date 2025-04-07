/**
 *
 */

#pragma once

#include <deque>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Types.hpp"
#include "AssetManager/AssetManager.hpp"
#include "Audio/AudioSystem.hpp"
#include "Audio/Volume.hpp"
#include "Runtime/Engine/Shader.hpp"
#include "Runtime/Engine/VertexBuffer.hpp"
#include "Runtime/Engine/Backends/OpenGL/OpenGLVertexBuffer.hpp"
#include "Scene/Scene.hpp"

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

            virtual void OnInit() = 0;
            virtual void OnUpdate() = 0;
            virtual void OnDestroy() = 0;
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
            virtual void RenderCircle(GLuint shaderProgram, GLuint VAO, GLsizei vertexCount) = 0;
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
            void RenderCircle(GLuint shaderProgram, GLuint VAO, GLsizei vertexCount) override;

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
            static std::vector<float> GenerateCircleVertices(float radius, int segments);

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

            void RenderQuad(GLuint shaderProgram, GLuint VAO) const;
            void RenderCircle(GLuint shaderProgram, GLuint VAO, GLsizei vertexCount) const;

        public:
            static GameEngineApi& getInstance();
        
            [[nodiscard]] IRenderer* GetRenderer() const;

        private:
            GameEngineApi();
            ~GameEngineApi();

        private:
            IRenderer* m_renderer;
    };
}
 
