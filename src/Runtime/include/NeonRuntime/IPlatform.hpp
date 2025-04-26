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

#include <string>

#include <NeonRuntime/ITextBuffer.hpp>
#include <NeonRuntime/IVertexBuffer.hpp>

namespace Neon
{
    class Application;

    class IPlatform
    {
        public:
            IPlatform() = default;
            virtual ~IPlatform() = default;

            virtual bool Initialize(int width, int height, const char* title) = 0;
            virtual void Run(Application* game) = 0;

            virtual IShader* CreateShader(const std::string& vertexPath, const std::string& fragmentPath) = 0;
            virtual IVertexBuffer* CreateVertexBuffer(float* vertices, int* indices, size_t size) = 0;
            virtual ITextBuffer* CreateTextBuffer(size_t bufferSize) = 0;
    };
}