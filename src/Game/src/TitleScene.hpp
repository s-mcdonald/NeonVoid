#pragma once

#include <iostream>
#include <cmath>

#include "../../GameEngine/src/Runtime/Runtime.hpp"

namespace Neon
{
    class TitleScene : public Scene
    {
        public:
            TitleScene(Platform* platform);
            ~TitleScene();

            void OnUpdate();
    };
}
