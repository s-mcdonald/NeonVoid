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

     // Next refactor here is to create a separate MyGame class that abstracts a bit more, but this is now looking
     // much better for entry.
     Game game;
 
     LoadGameData(&game);
 
     if (game.Initialize(800, 600, "Neon Void (0.0.2)"))
     {
         game.Run();
     }
 }
 
 