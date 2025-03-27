/**
 * 
 */

#include <iostream>

#include <chrono>
#include <thread>
#include <miniaudio.h>

#include "Game/NeonFunctions.hpp"
#include "Runtime/Runtime.hpp"

int main()
{
    using namespace Neon;

    AudioSystem player;
    player.Play("./neon_void_into.mp3");

    // a dramatic pause before opening title
    // honmestly this is only for development until audio is in..
    std::this_thread::sleep_for(std::chrono::seconds(2));

    Game game;
    GameEngine gameEngine;

    // We configure our game here
    // potentially yaml file for scenes ect.
    // @todo: Nope, this is not how we should configure a game
    LoadGameData(&game, gameEngine);

    if (gameEngine.Initialize(800, 600, "Neon Game")) 
    {
        gameEngine.Run(&game);
    }

    player.Stop();

    // Did I forget to return ?? ;)
}

