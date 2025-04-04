/**
 * 
 */
#include <iostream>

#include "../Runtime.hpp"

namespace Neon 
{
    GameEngine::GameEngine() : m_platform(nullptr)
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "GameEngine::Constructor called\n";
        #endif

        #ifdef NEON_BUILD_OPENGL
            m_platform = new Neon::OpenGL();
        #endif

        #ifdef NEON_BUILD_VULKAN
            m_platform = new Neon::OpenGL();
        #endif
    }

    GameEngine::~GameEngine() 
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "GameEngine::Destructor called\n";
        #endif

        delete m_platform;
    }

    bool GameEngine::Initialize(const int width, const int height, const char* title) const
    {
        return m_platform->Initialize(width, height,title);
    }

    void GameEngine::Run(Game* game) const
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
            // let's also do an assert here, i think cherno did this too.
            // need to learn more about compile time asserts.
            return nullptr;
        #endif
    }

}
