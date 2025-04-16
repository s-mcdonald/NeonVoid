/**
 * {SourceHeader}
 */

#pragma once

#include <string>

#include <Runtime/Backends/IShader.hpp>

#include "Backends/OpenGL/OpenGLRenderer.hpp"

#ifdef NEON_BUILD_OPENGL
#include <Runtime/Backends/OpenGL/OpenGL.hpp>
#include <Runtime/Backends/OpenGL/OpenGLShader.hpp>
#include <Runtime/Backends/OpenGL/OpenGLVertexBuffer.hpp>
#elif defined(NEON_BUILD_VULKAN)
#else
#endif


namespace Neon
{
    class IRenderer;

    typedef void* WindowHandlePtr;

    class GameEngineApi
    {
        public:
            GameEngineApi(const GameEngineApi&) = delete;
            GameEngineApi& operator=(const GameEngineApi&) = delete;

        public:
            static GameEngineApi& GetInstance();
            [[nodiscard]] IRenderer* GetRenderer() const;

            static IPlatform* CreatePlatform();

            IVertexBuffer* CreateVertexBuffer(float* vertices, size_t size);
            IShader* CreateShader(std::string vertexPath, std::string fragmentPath);

            void SetWindow(WindowHandlePtr window);
            [[nodiscard]] WindowHandlePtr GetWindowAsPtr() const;

        private:
            GameEngineApi();
            ~GameEngineApi();

        private:
            WindowHandlePtr mx_window{nullptr};
            IRenderer* m_renderer;
    };
}
