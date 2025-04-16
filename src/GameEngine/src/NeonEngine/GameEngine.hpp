/**
 * {SourceHeader}
 */

#pragma once

#include <string>

#include <Runtime/ExtRuntime.hpp>

namespace Neon
{
    // Move this to the Application class
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

        private:
            IPlatform* m_platform;
    };
}
