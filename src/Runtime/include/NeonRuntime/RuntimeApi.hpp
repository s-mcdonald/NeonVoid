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

#pragma once

#include <NeonRuntime/IntRuntime.hpp>
#include <NeonRuntime/Backends/OpenGL.hpp>
#include <NeonRuntime/ITextBuffer.hpp>
#include <NeonRuntime/IVertexBuffer.hpp>

namespace Neon
{
    class RuntimeApi
    {
        public:
            RuntimeApi(const RuntimeApi&) = delete;
            RuntimeApi& operator=(const RuntimeApi&) = delete;
            static RuntimeApi& GetInstance();

            [[nodiscard]] IRenderer* GetRenderer() const;

            [[nodiscard]] IPlatform* GetPlatform();
            IVertexBuffer* CreateVertexBuffer(float* vertices, int* indices, size_t size);
            ITextBuffer* CreateTextBuffer(size_t bufferSize);

        private:
            RuntimeApi();
            ~RuntimeApi();

            IRenderer* m_renderer;
#ifdef NEON_BUILD_OPENGL
            OpenGL m_platform;
#elif defined(NEON_BUILD_VULKAN)
#else
#endif
    };
}
