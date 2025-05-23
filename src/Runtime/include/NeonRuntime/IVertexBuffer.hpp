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

#include <cstdint>

namespace Neon
{
    class IVertexBuffer
    {
        public:
            virtual ~IVertexBuffer() = default;

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;
            virtual void UpdateData(const void* data, size_t size) = 0;
            virtual void UpdateIndices(const void* indices, size_t size) = 0;

            virtual uint32_t GetVao() = 0;
            virtual uint32_t GetVbo() = 0;
    };
}
