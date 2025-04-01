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

   
        // Add Quad / triangle
        auto* component = new QuadComponent();
        scene->AddComponent("vao.triangle", component);

        // Add Audio
        auto* introMusic = new AudioComponent("./assets/audio/neon_void_intro.mp3");
        scene->AddComponent("aud.intro", introMusic);

        // Add Text
        auto* titleText = new TextComponent("Neon Void: A Saga", 16);
        scene->AddComponent("text.title", titleText);

        // Add Trigger to move to new Scene after
    }
}
