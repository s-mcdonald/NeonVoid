/**
 * {SourceHeader}
 */

#pragma once

#include <vector>

#include <Runtime/Runtime.hpp>
#include <Runtime/Runtime/Backends/Platform.hpp>

namespace Neon
{
    class OpenGL final : public Platform
    {
        public:
            OpenGL();
            ~OpenGL() override;

            bool Initialize(int width, int height, const char* title) override;

            void Run(Application* game) override;

            static std::vector<float> GenerateCircleVertices(float radius, int segments);

        protected:
            GLFWwindow* m_window;
            bool m_openGlInitialized = false;
            AssetManager* m_assetManager;
    };
}