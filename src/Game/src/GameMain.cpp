/**
 * 
 */

#include <iostream>

#include <chrono>
#include <thread>

#include "NeonFunctions.hpp"
#include "../../GameEngine/src/Runtime/Runtime.hpp"
 
 int main()
 {
     using namespace Neon;

     // once initialized, game will load from its working/launch dir, load scenes ect.
     //  Eseentially this is the only code I want in entry.
     // Game game; 
     // if (game.Initialize()) 
     // {
     //    game.Run();
     // }


 
     Game game;
     GameEngine gameEngine;

        // @todo: I think the gameEngine should be injected into the game, 
        //          so that its what runbs the game, and does not need to be defined 
        //          in the main entry point, the game manages the engine.
 
     LoadGameData(&game, gameEngine);
 
     if (gameEngine.Initialize(800, 600, "Neon Void (0.0.2)")) 
     {
         gameEngine.Run(&game);
     }
 }
 
 