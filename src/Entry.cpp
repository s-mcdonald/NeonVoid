/**
 * 
 */

#include <iostream>

#include "Runtime/Runtime.h"

int main(int argc, char** argv)
{
    Neon::Runtime gameEngine;

    if (gameEngine.Initialize(800, 600, "Neon Game")) 
    {
        gameEngine.Run();
    }

    // Did I forget to return ?? ;)
}