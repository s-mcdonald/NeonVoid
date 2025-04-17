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
    #include <Runtime/Backends/OpenGL/OpenGLHeaders.hpp>

    // Core Abstractions ;;
    #include <Runtime/ExtRuntime.hpp>
    #include <Runtime/Factory/ShaderFactory.hpp>

    // OpenGL Abstractions ;;
    #include <Runtime/RuntimeApi.hpp>
    #include <Runtime/Backends/OpenGL/OpenGL.hpp>
    #include <Runtime/Backends/OpenGL/OpenGLInput.hpp>
    #include <Runtime/Backends/OpenGL/OpenGLRenderer.hpp>
    #include <Runtime/Backends/OpenGL/OpenGLShader.hpp>
    #include <Runtime/Backends/OpenGL/OpenGLVertexBuffer.hpp>

#elif defined(NEON_BUILD_VULKAN)

#else

#endif