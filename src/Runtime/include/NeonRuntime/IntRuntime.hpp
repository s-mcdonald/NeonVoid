/**
 * {SourceHeader}
 */

#pragma once

#include <cmath>
#include <string>
#include <cstddef>
#include <vector>

#ifdef NEON_BUILD_OPENGL

    // OpenGL Header list
    #include <NeonRuntime/Backends/OpenGLHeaders.hpp>

    // Core Abstractions ;;
    #include <NeonRuntime/ExtRuntime.hpp>
    #include <NeonRuntime/ShaderFactory.hpp>

    // OpenGL Abstractions ;;
    #include <NeonRuntime/Backends/OpenGL.hpp>
    #include <NeonRuntime/Backends/OpenGLRenderer.hpp>
    #include <NeonRuntime/Backends/OpenGLShader.hpp>
    #include <NeonRuntime/Backends/OpenGLVertexArray.hpp>
    #include <NeonRuntime/Backends/OpenGLVertexBuffer.hpp>
    #include <NeonRuntime/Backends/OpenGLInput.hpp>
    #include <NeonRuntime/RuntimeApi.hpp>

#elif defined(NEON_BUILD_VULKAN)

#else

#endif