/**
 * 
 */

#include <iostream>

#include "Game/Game.h"
#include "Game/Utils/NeonFunctions.h"
#include "Runtime/GameEngine.h"

int main()
{
    using namespace Neon;

    GameEngine gameEngine;
    Game* game;
    game = new Game();

    // We configure our game here
    // potentially yaml file for scenes ect.
    LoadGameData(game);

    if (gameEngine.Initialize(800, 600, "Neon Game")) 
    {
        gameEngine.Run(game);
    }

    delete game;

    // Did I forget to return ?? ;)
}

