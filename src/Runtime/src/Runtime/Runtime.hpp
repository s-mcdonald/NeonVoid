/**
 * {SourceHeader}
 */

#pragma once

#include <cstddef>                          // For size_t

#ifdef NEON_BUILD_OPENGL

    // Game and Game Engine should ONLY see the below interfaces
    #include <Runtime/Backends/IWindow.hpp>
    #include <Runtime/Backends/IRenderer.hpp>
    #include <Runtime/Backends/Platform.hpp>
    #include <Runtime/Backends/Shader.hpp>
    #include <Runtime/Backends/VertexBuffer.hpp>

    // Right now Game and Engine have direct dependencies on these below and shouldn't!
    #include <Runtime/Backends/OpenGL/GameEngineApi.hpp>
    #include <Runtime/Backends/OpenGL/OpenGLRenderer.hpp>
    #include <Runtime/Backends/OpenGL/OpenGLVertexBuffer.hpp>


#elif defined(NEON_BUILD_VULKAN)

#else

#endif