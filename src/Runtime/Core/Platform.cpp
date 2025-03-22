/**
 * 
 */
#include <iostream>

#include "Runtime/Runtime.hpp"

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
        return true;
    }

    void Platform::Run(Game* game) 
    {
        //
    }
    
    void Platform::TriggerPostRedisplay()
    {
        //
    }

    void Platform::CleanResources() 
    {
        //
    }
}
