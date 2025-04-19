/**
 * {SourceHeader}
 */

#pragma once

namespace Neon
{
    class IWindow
    {
        public:
            virtual ~IWindow() = default;

        public:
            [[nodiscard]] virtual void* GetNativeWindowHandle() const = 0;

        // @todo: Implement these below so we can abstract away the runtime game loop
    };
}

