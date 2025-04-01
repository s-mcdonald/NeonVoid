/**
 *
 */

#include <iostream>

#include "NeonFunctions.hpp"
#include "Scenes.hpp"
#include "../../GameEngine/src/Runtime/Runtime.hpp"

void Neon::LoadGameData(Game* game, const GameEngine& gameEngine)
{
    using namespace Neon;
    {
        auto* scene = new TitleScene(SceneType::Title, gameEngine.GetPlatform());
        auto* gamePlayScene = new GamePlayScene(SceneType::Gameplay, gameEngine.GetPlatform());

        game->AddScene(scene);
        game->AddScene(gamePlayScene);
    }
}
