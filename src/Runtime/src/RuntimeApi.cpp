/**
 * {SourceHeader}
 */

#include <NeonRuntime/IntRuntime.hpp>
#include <NeonRuntime/PlatformFactory.hpp>

namespace Neon
{
    typedef void* WindowHandlePtr;

    RuntimeApi& RuntimeApi::GetInstance()
    {
        static RuntimeApi instance;
        return instance;
    }

    RuntimeApi::RuntimeApi() : mx_window(nullptr)
    {
        m_renderer = new OpenGLRenderer();
    }

    RuntimeApi::~RuntimeApi()
    {
        delete m_renderer;
    }

    auto RuntimeApi::GetRenderer() const -> IRenderer*
    {
        return m_renderer;
    }

    std::vector<float> RuntimeApi::GenerateCircleVertices(const float radius, const int segments)
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

    // Renderer Primitives

    IPlatform* RuntimeApi::CreatePlatform()
    {
        return PlatformFactory::CreatePlatform();
    }

    IVertexBuffer* RuntimeApi::CreateVertexBuffer(float* vertices, size_t size)
    {
        return m_bufferFactory.CreateVertexBuffer(vertices, size);
    }

    IShader* RuntimeApi::CreateShader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        return m_shaderFactory.CreateShader(vertexPath, fragmentPath);
    }
}
