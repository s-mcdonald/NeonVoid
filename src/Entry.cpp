/**
 * 
 */

#include <iostream>

#include <chrono>
#include <thread>

#include "Game/NeonFunctions.hpp"
#include "Runtime/Runtime.hpp"

int main()
{
    using namespace Neon;

    Game game;
    GameEngine gameEngine;

    LoadGameData(&game, gameEngine);

    if (gameEngine.Initialize(800, 600, "Neon Void (0.0.1)")) 
    {
        gameEngine.Run(&game);
    }
}

