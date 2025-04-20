/**
 * {SourceHeader}
 */

#pragma once

#include <vector>

namespace Neon
{
    class VerticesFactory
    {
        public:
            VerticesFactory() = default;
            ~VerticesFactory() = default;
        public:
            std::vector<float> GenerateCircleVertices(float radius, int segments);
    };
}

