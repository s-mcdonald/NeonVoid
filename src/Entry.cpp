/**
 * 
 */

#include <iostream>

#include "Runtime/OpenGL.h"
#include "Runtime/Core/Platform.h"
#include "Runtime/GameEngine.h"

int main()
{
    Neon::GameEngine gameEngine;

    if (gameEngine.Initialize(800, 600, "Neon Game")) 
    {
        gameEngine.Run();
    }

    // Did I forget to return ?? ;)
}