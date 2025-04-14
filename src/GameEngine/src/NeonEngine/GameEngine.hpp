/**
 * {SourceHeader}
 */

#pragma once

#include <NeonEngine/Runtime.hpp>
#include <NeonEngine/Runtime/Backends/Platform.hpp>
#include <NeonEngine/Runtime/Backends/Shader.hpp>
#include <NeonEngine/Runtime/Backends/VertexBuffer.hpp>

namespace Neon
{
    class GameEngine
    {
        public:
            GameEngine();
            ~GameEngine();

        public:
            bool Initialize(int width, int height, const char* title) const;
            void Run(Application* application) const;

            [[nodiscard]] Platform* GetPlatform() const;

            static VertexBuffer* CreateVertexBuffer(float* vertices, size_t size);
            static Shader* CreateShader(std::string vertexPath, std::string fragmentPath);

        private:
            Platform* m_platform;
    };
}
