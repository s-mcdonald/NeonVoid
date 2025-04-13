#pragma once

#include <vector>

#include <Runtime/Runtime.hpp>
#include <Runtime/Runtime/Backends/Platform.hpp>
#include <Runtime/Runtime/Backends/OpenGL/OpenGLHeaders.hpp>

namespace Neon
{
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
}