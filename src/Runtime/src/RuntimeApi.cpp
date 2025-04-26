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
#include <NeonRuntime/PlatformFactory.hpp>

namespace Neon
{
    typedef void* WindowHandlePtr;

    RuntimeApi& RuntimeApi::GetInstance()
    {
        static RuntimeApi instance;
        return instance;
    }

    RuntimeApi::RuntimeApi()
    {
        m_renderer = new OpenGLRenderer();
    }

    RuntimeApi::~RuntimeApi()
    {
        delete m_renderer;
    }

    auto RuntimeApi::GetRenderer() const -> IRenderer*
    {
        return m_renderer;
    }

    IPlatform* RuntimeApi::GetPlatform()
    {
        return &m_platform;
    }

    IVertexBuffer* RuntimeApi::CreateVertexBuffer(float* vertices, int* indices, size_t size)
    {
        return m_platform.CreateVertexBuffer(vertices, indices, size);
    }

    ITextBuffer* RuntimeApi::CreateTextBuffer(size_t size)
    {
        return m_platform.CreateTextBuffer(size);
    }
}
