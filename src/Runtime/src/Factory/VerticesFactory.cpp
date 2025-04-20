/**
 * {SourceHeader}
 */

#include <NeonRuntime/IntRuntime.hpp>
#include <NeonRuntime/VerticesFactory.hpp>

namespace Neon
{
    std::vector<float> VerticesFactory::GenerateCircleVertices(float radius, int segments)
    {
        std::vector<float> vertices;

        vertices.push_back(0.0f); // X
        vertices.push_back(0.0f); // Y

        const float angleStep = 2.0f * M_PI / segments;

        for (auto i = 0; i <= segments; ++i)
        {
            const float angle = i * angleStep;
            vertices.push_back(std::cos(angle) * radius); // X
            vertices.push_back(std::sin(angle) * radius); // Y
        }

        return vertices;
    }

    // really this is only for testing & development
    // actual vertices will come from the yaml pre-compiled
    std::vector<float> VerticesFactory::GenerateBasicTriangleVertices()
    {
        return {
            -0.5f, -0.5f,    // Bottom left
             0.5f, -0.5f,    // Bottom right
             0.0f,  0.5f     // Top
        };
    }
}
