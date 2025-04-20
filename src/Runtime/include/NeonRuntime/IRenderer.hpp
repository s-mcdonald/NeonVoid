/**
 * {SourceHeader}
 */

#pragma once

#include <cstdint>

namespace Neon
{
    class IRenderer
    {
        public:
            virtual ~IRenderer() = default;

            virtual void BeginFrame() = 0;
            virtual void EndFrame() = 0;
            virtual void RenderTriangle(uint32_t shaderProgram, uint32_t VAO, int vertexCount) = 0;
    };
}