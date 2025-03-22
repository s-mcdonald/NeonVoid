/**
 * 
 */

#include <iostream>

#include "Game/NeonFunctions.hpp"

#include "Runtime/Runtime.hpp"

int main()
{
    using namespace Neon;

    GameEngine gameEngine;
    Game* game;
    game = new Game();

    // We configure our game here
    // potentially yaml file for scenes ect.
    LoadGameData(game, gameEngine);

    if (gameEngine.Initialize(800, 600, "Neon Game")) 
    {
        gameEngine.Run(game);
    }

    delete game;

    // Did I forget to return ?? ;)
}

