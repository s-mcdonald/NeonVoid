/**
 * {SourceHeader}
 */

#pragma once

#include <Runtime/ExtRuntime.hpp>

namespace Neon
{
    class RuntimeBridge
    {
        public:
            RuntimeBridge();
            ~RuntimeBridge();

        public:
            bool Initialize(int width, int height, const char* title) const;
            void Run(Application* application) const;

            [[nodiscard]] IPlatform* GetPlatform() const;

        private:
            IPlatform* m_platform;
    };
}
