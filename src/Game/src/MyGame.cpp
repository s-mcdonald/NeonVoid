/**
 * {SourceHeader}
 */

#include <NeonEngine/All.hpp>

#include "MyGame.hpp"
#include "Scenes/GamePlayScene.hpp"
#include "Scenes/TitleScene.hpp"

namespace Neon
{
    MyGame::MyGame()
    {
        YamlReader yamlReader("/home/sam/Game/Neon/build/assets/game.yaml");

        yamlReader.Load();

        // eventually we should use a scene loader where the scene will load when needed
        // and not be instantiated at load time.
       // auto* scene = new TitleScene(SceneType::Title);
        //auto* gamePlayScene = new GamePlayScene(SceneType::Gameplay);

        //AddScene(scene);
        //AddScene(gamePlayScene);
    }

    bool MyGame::Initialize() const
    {
        return Application::Initialize(800, 600, "Neon Void (0.0.4)");
    }
}