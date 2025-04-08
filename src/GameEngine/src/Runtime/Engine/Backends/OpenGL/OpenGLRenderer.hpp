#pragma once

#include <Runtime/Engine/Backends/IRenderer.hpp>

namespace Neon
{
    // Forward..
    class TextComponent;

    class OpenGLRenderer final : public IRenderer
    {
        public:
            OpenGLRenderer() = default;
            ~OpenGLRenderer() override = default;

        public:
            void BeginFrame() override;
            void EndFrame() override;
            void RenderText(const TextComponent& component) override;
            void RenderQuad(uint32_t shaderProgram, uint32_t VAO) override;
            void RenderCircle(uint32_t shaderProgram, uint32_t VAO, GLsizei vertexCount) override;
    };
}