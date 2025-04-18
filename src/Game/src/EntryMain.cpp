/**
 * {SourceHeader}
 */

#include "Core/MyGame.hpp"

int main()
 {
     Neon::MyGame game;

     if (game.Initialize())
     {
         game.Run();
     }
 }
