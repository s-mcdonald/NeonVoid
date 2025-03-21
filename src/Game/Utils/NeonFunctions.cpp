/**
 *
 */

#include <iostream>

#include "Game/Game.h"
#include "Game/Scene.h"
#include "Game/Utils/NeonFunctions.h"

void Neon::LoadGameData(Game* game)
{
    using namespace Neon;
    {
        std::cout << "Entry ==> LoadGameData(game)\n";

        Scene* onlyScene = new Scene();
        game->AddScene(onlyScene);
    }
}
