/**
 * {SourceHeader}
 */

#pragma once

#include <NeonEngine/Types.hpp>

namespace Neon
{
    class IWindow
    {
        public:
            virtual ~IWindow() = default;

        public:
            [[nodiscard]] virtual void* GetNativeWindowHandle() const = 0;

        // @todo: Implement these below so we can abstract away the runtime game loop

        //
        // virtual ~IWindow() = default;
        // virtual bool Initialize(WindowDimention width, WindowDimention height, const char* title) = 0;
        // virtual void PollEvents() = 0;
        // virtual bool ShouldClose() const = 0;
        // virtual void SwapBuffers() const = 0;
        // virtual void Destroy() = 0;
        //
    };
}

