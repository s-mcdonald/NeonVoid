/**
 * 
 */

#include <iostream>

#include "Runtime/GameEngine.h"
#include "Game/Game.h"

int main()
{
    using namespace Neon;

    GameEngine gameEngine;
    Game* game;
    game = new Game();

    // We need a way to confiure the game since our gameEngine wil be empty
    // LoadGameData(gameEngine);

    if (gameEngine.Initialize(800, 600, "Neon Game")) 
    {
        gameEngine.Run(game);
    }

    delete game;

    // Did I forget to return ?? ;)
}

