/**
 * {SourceHeader}
 */

#pragma once

#include <Backends/OpenGL/OpenGLHeaders.hpp>
#include <Backends/IPlatform.hpp>

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
            AssetManager* m_assetManager;
    };
}