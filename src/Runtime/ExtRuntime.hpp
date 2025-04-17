/**
 * {SourceHeader}
 */

#pragma once

#include <cstddef>

#ifdef NEON_BUILD_OPENGL

    #include <Runtime/Backends/IInput.hpp>
    #include <Runtime/Backends/IWindow.hpp>
    #include <Runtime/Backends/IRenderer.hpp>
    #include <Runtime/Backends/IPlatform.hpp>
    #include <Runtime/Backends/IShader.hpp>
    #include <Runtime/Backends/IVertexBuffer.hpp>
    #include <Runtime/RuntimeApi.hpp>

#elif defined(NEON_BUILD_VULKAN)

#else

#endif