/**
 * {SourceHeader}
 */

#pragma once

namespace Neon
{
    class Application;

    class Platform
    {
        public:
            Platform() = default;
            virtual ~Platform() = default;

        public:
            virtual bool Initialize(int width, int height, const char* title) = 0;
            virtual void Run(Application* game) = 0;

    };
}