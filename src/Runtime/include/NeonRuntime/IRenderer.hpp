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
#include <string>

#include <NeonRuntime/Backends/OpenGLVertexBuffer.hpp>
#include <NeonRuntime/Backends/OpenGLTextBuffer.hpp>

namespace Neon
{
    class IRenderer
    {
        public:
            virtual ~IRenderer() = default;

            virtual void BeginFrame() = 0;
            virtual void EndFrame() = 0;
            virtual void RenderTriangle(uint32_t shaderProgram, uint32_t VAO, int vertexCount) = 0;
            virtual void RenderText(uint32_t shaderProgram, ITextBuffer* textbuffer, const std::string& text) = 0;
            virtual void LoadFont(const std::string& fontPath) = 0;
    };
}
