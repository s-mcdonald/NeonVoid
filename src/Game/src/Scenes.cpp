/**
 * 
 */
#include <iostream>
#include <cmath>

#include "../../GameEngine/src/Runtime/Runtime.hpp"
#include "Scenes.hpp"

namespace Neon
{
    TitleScene::TitleScene(const SceneType type, Platform* platform)
        : Scene(type, platform)
    {
        //
    }

    void TitleScene::OnUpdate()
    {
        std::cout << "Child \n";

        if (auto* x = GetComponent("aud.intro"))
        {
            auto* ac = dynamic_cast<AudioComponent*>(x);
            ac->TriggerPlayOnce();
        }

        Scene::OnUpdate();
    }


    GamePlayScene::GamePlayScene(const SceneType type, Platform* platform)
        : Scene(type, platform)
    {
        //
    }

    void GamePlayScene::OnUpdate()
    {
        std::cout << "Child \n";

        Scene::OnUpdate();
    }
}
