/**
 * {SourceHeader}
 */

#pragma once

#include <cstddef>                          // For size_t

#ifdef NEON_BUILD_OPENGL

    // Core Abstractions ;;
    #include <Runtime/Backends/Input.hpp>
    #include <Runtime/Backends/IWindow.hpp>
    #include <Runtime/Backends/IRenderer.hpp>
    #include <Runtime/Backends/IPlatform.hpp>
    #include <Runtime/Backends/IShader.hpp>
    #include <Runtime/Backends/IVertexBuffer.hpp>

#elif defined(NEON_BUILD_VULKAN)

#else

#endif