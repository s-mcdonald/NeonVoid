/**
 * 
 */
#include <iostream>

#include "Game/Game.h"
#include "Runtime/OpenGL.h"
#include "Runtime/Core/Platform.h"


namespace Neon 
{
    Platform::Platform()
    {
        std::cout << "Platform::Constructor called\n";
    }

    Platform::~Platform() 
    {
        std::cout << "Platform::Destructor called\n";
        CleanResources();
    }

    bool Platform::Initialize(int width, int height, const char* title) 
    {
        //
        return true;
    }

    void Platform::Run(Game* game) 
    {
        //
    }

    void Platform::CleanResources() 
    {
        //
    }
}
