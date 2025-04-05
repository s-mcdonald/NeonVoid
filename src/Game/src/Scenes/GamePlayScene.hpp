#pragma once

#include <iostream>
#include <cmath>

#include "../../GameEngine/src/Runtime/Runtime.hpp"

namespace Neon
{
    class GamePlayScene final : public Scene
    {
        public:
            explicit GamePlayScene(SceneType type);
            ~GamePlayScene() override = default;

            void OnInit() override;
            void OnUpdate() override;
    };
}
