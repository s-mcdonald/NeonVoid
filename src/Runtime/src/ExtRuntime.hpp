/**
 * {SourceHeader}
 */

#pragma once

#include <cstddef>

#ifdef NEON_BUILD_OPENGL

    #include <Backends/IInput.hpp>
    #include <Backends/IShader.hpp>
    #include <Backends/IWindow.hpp>
    #include <Backends/IRenderer.hpp>
    #include <Backends/IPlatform.hpp>
    #include <Backends/IVertexArray.hpp>
    #include <Backends/IFrameBuffer.hpp>
    #include <Backends/IVertexBuffer.hpp>
    #include <RuntimeApi.hpp>

#elif defined(NEON_BUILD_VULKAN)

#else

#endif