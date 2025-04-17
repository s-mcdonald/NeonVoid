/**
 * {SourceHeader}
 */

#include <Runtime/IntRuntime.hpp>

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

    IRenderer* RuntimeApi::GetRenderer() const
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
#ifdef NEON_BUILD_OPENGL
        // System::GetPlatform()
        return new Neon::OpenGL();
#elif defined(NEON_BUILD_VULKAN)
        //
#else
        return nullptr;
#endif
    }

    IVertexBuffer* RuntimeApi::CreateVertexBuffer(float* vertices, size_t size)
    {
#ifdef NEON_BUILD_OPENGL
        return new OpenGLVertexBuffer(vertices, size);
#elif defined(NEON_BUILD_VULKAN)
        // return new VulkanVertexBuffer(vertices, size);
#else
        // let's also do an assert here, I think cherno did this too.
        // need to learn more about compile time asserts.
        return nullptr;
#endif
    }

    IShader* RuntimeApi::CreateShader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        return m_shaderFactory.CreateShader(vertexPath, fragmentPath);
    }
}
