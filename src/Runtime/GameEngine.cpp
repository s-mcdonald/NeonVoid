/**
 * 
 */
#include <iostream>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    GameEngine::GameEngine() : m_platform(nullptr)
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "GameEngine::Constructor called\n";
        #endif

        // On the heap you go
        m_platform = new Neon::OpenGL();
    }

    GameEngine::~GameEngine() 
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "GameEngine::Destructor called\n";
        #endif

        delete m_platform;
    }

    bool GameEngine::Initialize(int width, int height, const char* title) 
    {
        return m_platform->Initialize(width, height,title);
    }

    void GameEngine::Run(Game* game) 
    {
        m_platform->Run(game);
    }

    Platform* GameEngine::GetPlatform() const
    {
        return m_platform;
    }
}
