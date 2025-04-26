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

#include <NeonRuntime/IPlatform.hpp>
#include <NeonRuntime/Backends/OpenGLHeaders.hpp>

namespace Neon
{
    class AssetManager;

    class OpenGL final : public IPlatform
    {
        public:
            OpenGL();
            ~OpenGL() override;

            bool Initialize(int width, int height, const char* title) override;

            void Run(Application* game) override;

            IShader* CreateShader(const std::string& vertexPath, const std::string& fragmentPath) override;
            IVertexBuffer* CreateVertexBuffer(float* vertices, size_t size) override;
            ITextBuffer* CreateTextBuffer(size_t bufferSize) override;

        protected:
            GLFWwindow* m_window;
            bool m_openGlInitialized = false;
    };
}
