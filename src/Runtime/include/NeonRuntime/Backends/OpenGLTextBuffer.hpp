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

#include <NeonRuntime/ITextBuffer.hpp>

namespace Neon
{
    class OpenGLTextBuffer final : public ITextBuffer
    {
        public:
            OpenGLTextBuffer() = default;
            ~OpenGLTextBuffer() override;

            void Init() override;
            void Update() const override {};

            void Bind() const override;
            void Unbind() const override;

            uint32_t GetVao() override;
            uint32_t GetVbo() override;

        private:
            uint32_t m_VAO = 0;
            uint32_t m_VBO = 0;
    };
}
