/**
 * {SourceHeader}
 */

#pragma once

#include <NeonEngine/Runtime/Backends/IRenderer.hpp>

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
            void RenderQuad(uint32_t shaderProgram, uint32_t VAO) override;
            void RenderCircle(uint32_t shaderProgram, uint32_t VAO, int vertexCount) override;
    };
}
