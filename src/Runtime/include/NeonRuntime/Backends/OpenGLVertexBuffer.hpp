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

#include <NeonRuntime/IVertexBuffer.hpp>

namespace Neon
{
    class OpenGLVertexBuffer final : public IVertexBuffer
    {
        public:
            OpenGLVertexBuffer(const float*, size_t);
            ~OpenGLVertexBuffer() override;

            void Bind() const override;
            void Unbind() const override;
            void UpdateData(const void* data, size_t size) override;

            uint32_t GetVao() override;
            uint32_t GetVbo() override;

        private:
            const float* m_vertices;
            size_t m_size;
            uint32_t m_VAO{};
            uint32_t m_VBO{};
    };
}
