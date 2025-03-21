/**
 * 
 */
#include <iostream>

#include "Runtime/GameEngine.h"
#include "Runtime/OpenGL.h"

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

    void GameEngine::CleanResources() 
    {
        delete m_platform;
    }
}
