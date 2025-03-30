/**
 * 
 */
#include <iostream>
#include <cmath>

#include "../../GameEngine/src/Runtime/Runtime.hpp"
#include "Scenes.hpp"

namespace Neon
{
    TitleScene::TitleScene(SceneType type, Platform* platform)
        : Scene(type, platform)
    {
        //
    }
                
    TitleScene::~TitleScene()
    {
        //
    }

    void TitleScene::OnUpdate()
    {
        std::cout << "Child \n";

        auto* x = GetComponent("aud.intro");
        if (x)
        {
            AudioComponent* ac = static_cast<AudioComponent*>(x);
            ac->TriggerPlayOnce();
        }

        Scene::OnUpdate();
    }


    GamePlayScene::GamePlayScene(SceneType type, Platform* platform)
        : Scene(type, platform)
    {
        //
    }
                
    GamePlayScene::~GamePlayScene()
    {
        //
    }

    void GamePlayScene::OnUpdate()
    {
        std::cout << "Child \n";

        Scene::OnUpdate();
    }
}
