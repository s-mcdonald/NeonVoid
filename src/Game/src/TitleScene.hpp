#pragma once

#include <iostream>
#include <cmath>

#include "../../GameEngine/src/Runtime/Runtime.hpp"

namespace Neon
{
    class TitleScene : public Scene
    {
        public:
            TitleScene(SceneType type, Platform* platform);
            ~TitleScene();

            void OnUpdate();
    };
}
