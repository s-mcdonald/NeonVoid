/**
 * {SourceHeader}
 */

#include <NeonEngine/GameEngine.hpp>

#include <Runtime/ExtRuntime.hpp>

namespace Neon
{
    GameEngine::GameEngine() : m_platform(nullptr)
    {
        m_platform = RuntimeApi::CreatePlatform();
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
