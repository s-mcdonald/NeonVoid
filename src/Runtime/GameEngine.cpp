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
        m_platform = new Neon::OpenGL();
    }

    GameEngine::~GameEngine() 
    {
        std::cout << "GameEngine::Destructor called\n";
        CleanResources();
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

    void GameEngine::CleanResources() 
    {
        delete m_platform;
    }
}
