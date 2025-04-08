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
#include <Runtime/Components/Component.hpp>
#include <Runtime/Components/TextComponent.hpp>
#include "Runtime/Engine/Backends/Platform.hpp"
#include "Runtime/Engine/Backends/IRenderer.hpp"

namespace Neon 
{
    class Game;
 


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

            static uint32_t CompileShader(const char* source, GLenum shaderType);
            static uint32_t CreateShaderProgram(const char* vertexSource, const char* fragmentSource);
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

            void RenderQuad(uint32_t shaderProgram, uint32_t VAO) const;
            void RenderCircle(uint32_t shaderProgram, uint32_t VAO, GLsizei vertexCount) const;

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
 
