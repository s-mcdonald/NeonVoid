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
    #include <Backends/OpenGL/OpenGLHeaders.hpp>

    // Core Abstractions ;;
    #include <ExtRuntime.hpp>
    #include <Factory/ShaderFactory.hpp>

    // OpenGL Abstractions ;;
    #include <RuntimeApi.hpp>
    #include <Backends/OpenGL/OpenGL.hpp>
    #include <Backends/OpenGL/OpenGLInput.hpp>
    #include <Backends/OpenGL/OpenGLShader.hpp>
    #include <Backends/OpenGL/OpenGLRenderer.hpp>
    #include <Backends/OpenGL/OpenGLVertexArray.hpp>
    #include <Backends/OpenGL/OpenGLVertexBuffer.hpp>

#elif defined(NEON_BUILD_VULKAN)

#else

#endif