/**
 * {SourceHeader}
 */

#include <Runtime/Runtime.hpp>

#ifdef NEON_BUILD_OPENGL
#include <Runtime/Runtime/Backends/OpenGL/OpenGL.hpp>
#elif defined(NEON_BUILD_VULKAN)
#else
#endif

namespace Neon
{
    GameEngine::GameEngine() : m_platform(nullptr)
    {
        #ifdef NEON_BUILD_OPENGL
            m_platform = new Neon::OpenGL();
        #elif defined(NEON_BUILD_VULKAN)
            m_platform = new Neon::Vulkan();
        #else
                return nullptr;
        #endif
    }

    GameEngine::~GameEngine() 
    {
        delete m_platform;
    }

    bool GameEngine::Initialize(const int width, const int height, const char* title) const
    {
        return m_platform->Initialize(width, height,title);
    }

    void GameEngine::Run(Application* game) const
    {
        m_platform->Run(game);
    }

    Platform* GameEngine::GetPlatform() const
    {
        return m_platform;
    }

    VertexBuffer* GameEngine::CreateVertexBuffer(float* vertices, size_t size)
    {
        #ifdef NEON_BUILD_OPENGL
            return new OpenGLVertexBuffer(vertices, size);
        #elif defined(NEON_BUILD_VULKAN)
            return new VulkanVertexBuffer(vertices, size);
        #else
            // let's also do an assert here, I think cherno did this too.
            // need to learn more about compile time asserts.
            return nullptr;
        #endif
    }
}
