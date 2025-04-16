/**
 * {SourceHeader}
 */

#include <utility>
#include <NeonEngine/GameEngine.hpp>

#ifdef NEON_BUILD_OPENGL
#include <Runtime/Backends/OpenGL/OpenGL.hpp>

#elif defined(NEON_BUILD_VULKAN)
#else
#endif

namespace Neon
{
    GameEngine::GameEngine() : m_platform(nullptr)
    {
#ifdef NEON_BUILD_OPENGL
        // System::GetPlatform()
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

    void GameEngine::Run(Application* application) const
    {
        m_platform->Run(application);
    }

    IPlatform* GameEngine::GetPlatform() const
    {
        return m_platform;
    }
}
