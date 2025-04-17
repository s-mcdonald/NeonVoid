/**
 * {SourceHeader}
 */

#pragma once

#include <NeonEngine/All.hpp>

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
