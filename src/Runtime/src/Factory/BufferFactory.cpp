/**
 *    ███╗   ██╗███████╗ ██████╗ ███╗   ██╗
 *    ████╗  ██║██╔════╝██╔═══██╗████╗  ██║
 *    ██╔██╗ ██║█████╗  ██║   ██║██╔██╗ ██║
 *    ██║╚██╗██║██╔══╝  ██║   ██║██║╚██╗██║
 *    ██║ ╚████║███████╗╚██████╔╝██║ ╚████║
 *    ╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═══╝
 * ========================================
 *                 NeonVoid
 *         A 2D Game Engine in C++
 * ----------------------------------------
 * License: MIT
 * Copyright (c) : 2024 Sam McDonald
 * Repository: https://github.com/s-mcdonald/NeonVoid
 */

#include <NeonRuntime/IntRuntime.hpp>
#include <NeonRuntime/ITextBuffer.hpp>
#include <NeonRuntime/IVertexBuffer.hpp>
#include <NeonRuntime/BufferFactory.hpp>

namespace Neon
{
    IVertexBuffer* BufferFactory::CreateVertexBuffer(float* vertices, size_t size)
    {
#ifdef NEON_BUILD_OPENGL
        return new OpenGLVertexBuffer(vertices, size);
#elif defined(NEON_BUILD_VULKAN)
        return nullptr;
#else
        return nullptr;
#endif
    }

    ITextBuffer* BufferFactory::CreateTextBuffer(size_t bufferSize)
    {
#ifdef NEON_BUILD_OPENGL
        return new OpenGLTextBuffer();
#elif defined(NEON_BUILD_VULKAN)
        return nullptr;
#else
        return nullptr;
#endif
    }
}
