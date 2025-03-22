/**
 *
 */

#include <iostream>

#include "Runtime/Runtime.hpp"

#include "Game/NeonFunctions.hpp"

void Neon::LoadGameData(Game* game, GameEngine& gameEngine)
{
    using namespace Neon;
    {
        std::cout << "Entry ==> LoadGameData(game)\n";

        Scene* onlyScene = new Scene(gameEngine.GetPlatform());
        game->AddScene(onlyScene);
    }
}
