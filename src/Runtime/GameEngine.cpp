/**
 * 
 */
#include <iostream>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    GameEngine::GameEngine() : m_platform(nullptr)
    {
        std::cout << "GameEngine::Constructor called\n";

        // On the heap you go
        m_platform = new Neon::OpenGL();
    }

    GameEngine::~GameEngine() 
    {
        std::cout << "GameEngine::Destructor called\n";

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
