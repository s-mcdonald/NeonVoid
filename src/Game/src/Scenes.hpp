#pragma once

#include <iostream>
#include <cmath>

#include "../../GameEngine/src/Runtime/Runtime.hpp"

namespace Neon
{
    class TitleScene final : public Scene
    {
        public:
            TitleScene(SceneType type, Platform* platform);
            ~TitleScene() override = default;

            void OnUpdate() override;
    };

    class GamePlayScene final : public Scene
    {
        public:
            GamePlayScene(SceneType type, Platform* platform);
            ~GamePlayScene() override = default;

            void OnUpdate() override;
    };
}
