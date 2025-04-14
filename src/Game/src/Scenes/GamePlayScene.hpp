/**
 * {SourceHeader}
 */

#pragma once

#include <NeonEngine/NeonEngine.hpp>
#include <Runtime/Runtime.hpp>

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
