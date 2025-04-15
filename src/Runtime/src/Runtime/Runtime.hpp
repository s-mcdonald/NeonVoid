/**
 * {SourceHeader}
 */

#pragma once

#include <cstddef>                          // For size_t

#ifdef NEON_BUILD_OPENGL

    // OpenGL Header list
    #include <Runtime/Backends/OpenGL/OpenGLHeaders.hpp>

    // Game and Game Engine should ONLY see the below interfaces
    #include <Runtime/Container.hpp>

    // Core Abstractions ;;
    #include <Runtime/Backends/Input.hpp>
    #include <Runtime/Backends/IWindow.hpp>
    #include <Runtime/Backends/IRenderer.hpp>
    #include <Runtime/Backends/IPlatform.hpp>
    #include <Runtime/Backends/IShader.hpp>
    #include <Runtime/Backends/IVertexBuffer.hpp>

    // OpenGL Abstractions ;;
    #include <Runtime/Backends/OpenGL/OpenGL.hpp>
    #include <Runtime/Backends/OpenGL/OpenGLInput.hpp>
    #include <Runtime/Backends/OpenGL/OpenGLShader.hpp>
    #include <Runtime/Backends/OpenGL/GameEngineApi.hpp>
    #include <Runtime/Backends/OpenGL/OpenGLRenderer.hpp>
    #include <Runtime/Backends/OpenGL/OpenGLVertexBuffer.hpp>

#elif defined(NEON_BUILD_VULKAN)

#else

#endif