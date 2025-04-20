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

    std::vector<float> RuntimeApi::GenerateCircleVertices(float radius, const int segments)
    {
        return m_verticesFactory.GenerateCircleVertices(radius, segments);
    }

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
