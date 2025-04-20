/**
 * {SourceHeader}
 */

#pragma once

namespace Neon
{
    class Application;

    class IPlatform
    {
        public:
            IPlatform() = default;
            virtual ~IPlatform() = default;

            virtual bool Initialize(int width, int height, const char* title) = 0;
            virtual void Run(Application* game) = 0;
    };
}