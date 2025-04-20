/**
 * {SourceHeader}
 */

#pragma once

#include <NeonRuntime/IRenderer.hpp>

namespace Neon
{
    class OpenGLRenderer final : public IRenderer
    {
        public:
            OpenGLRenderer() = default;
            ~OpenGLRenderer() override = default;

        public:
            void BeginFrame() override;
            void EndFrame() override;
            void RenderTriangle(uint32_t shaderProgram, uint32_t VAO, int vertexCount) override;
            void RenderText(uint32_t shaderProgram, uint32_t VAO, const std::string& text) override;
    };
}
