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
        m_platform = new Neon::OpenGL();
    }

    GameEngine::~GameEngine() 
    {
        CleanResources();
    }

    bool GameEngine::Initialize(int width, int height, const char* title) 
    {
        return m_platform->Initialize(width, height,title);
    }

    void GameEngine::Run() 
    {
        m_platform->Run();
    }

    void GameEngine::CleanResources() 
    {
        delete m_platform;
    }
}
