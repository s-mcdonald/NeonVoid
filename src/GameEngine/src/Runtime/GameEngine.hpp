/**
 * {SourceHeader}
 */

#pragma once

#include <Runtime/Runtime/Backends/Platform.hpp>
#include <Runtime/Runtime/Backends/VertexBuffer.hpp>

namespace Neon
{
    class Application;

    class GameEngine
    {
        public:
            GameEngine();
            ~GameEngine();

        public:
            bool Initialize(int width, int height, const char* title) const;
            void Run(Application* game) const;

            [[nodiscard]] Platform* GetPlatform() const;

            static VertexBuffer* CreateVertexBuffer(float* vertices, size_t size);

        private:
            Platform* m_platform;
    };
}
