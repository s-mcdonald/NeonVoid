/**
 * 
 */
#include <iostream>
#include <cmath>

#include "../../GameEngine/src/Runtime/Runtime.hpp"
#include "TitleScene.hpp"

namespace Neon
{
    TitleScene::TitleScene(Platform* platform)
        : Scene(platform)
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
}
