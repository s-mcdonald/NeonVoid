/**
 * {SourceHeader}
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

        protected:
            GLFWwindow* m_window;
            bool m_openGlInitialized = false;
    };
}