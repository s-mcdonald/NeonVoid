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

            void OnUpdate() override;
    };

    class GamePlayScene : public Scene
    {
        public:
            GamePlayScene(SceneType type, Platform* platform);
            ~GamePlayScene();

            void OnUpdate() override;
    };
}
