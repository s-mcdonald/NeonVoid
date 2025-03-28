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

    }
                
    TitleScene::~TitleScene()
    {
        //
    }

    void TitleScene::OnUpdate()
    {     
        std::cout << "Child \n";
        //Scene::OnUpdate();
    }
}
