/**
 * {SourceHeader}
 */

#pragma once

#include <string>

#include <Runtime/Runtime.hpp>

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
            void Run(Application* application) const;

            [[nodiscard]] IPlatform* GetPlatform() const;

            static IVertexBuffer* CreateVertexBuffer(float* vertices, size_t size);
            static IShader* CreateShader(std::string vertexPath, std::string fragmentPath);

        private:
            IPlatform* m_platform;
    };
}
