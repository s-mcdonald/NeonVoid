/**
 *
 */

#include "MyGame.hpp"
#include "Scenes/TitleScene.hpp"
#include "Scenes/GamePlayScene.hpp"

namespace Neon
{
    MyGame::MyGame()
    {
        auto* scene = new TitleScene(SceneType::Title);
        auto* gamePlayScene = new GamePlayScene(SceneType::Gameplay);

        AddScene(scene);
        AddScene(gamePlayScene);
    }

    bool MyGame::Initialize() const
    {
        return Game::Initialize(800, 600, "Neon Void (0.0.3)");
    }
}