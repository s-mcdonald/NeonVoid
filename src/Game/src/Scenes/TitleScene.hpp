#pragma once

#include "../../GameEngine/src/Runtime/Runtime.hpp"

namespace Neon
{
    class TitleScene final : public Scene
    {
        public:
            explicit TitleScene(SceneType type);
            ~TitleScene() override = default;

            void OnInit() override;
            void OnUpdate() override;
    };
}
