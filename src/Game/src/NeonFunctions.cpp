/**
 *
 */

#include <iostream>

#include "NeonFunctions.hpp"
#include "Scenes.hpp"
#include "../../GameEngine/src/Runtime/Runtime.hpp"

void Neon::LoadGameData(Game* game)
{
    using namespace Neon;
    {
        auto* scene = new TitleScene(SceneType::Title);
        auto* gamePlayScene = new GamePlayScene(SceneType::Gameplay);

        game->AddScene(scene);
        game->AddScene(gamePlayScene);
    }
}
