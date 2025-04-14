/**
 * {SourceHeader}
 */

#pragma once

#include <NeonEngine/NeonEngine.hpp>
#include <Runtime/Backends/Platform.hpp>
#include <Runtime/Backends/Shader.hpp>
#include <Runtime/Backends/VertexBuffer.hpp>

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
