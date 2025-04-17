/**
 * {SourceHeader}
 */

#pragma once

#include <../../GameEngine/src/All.hpp>

namespace Neon
{
    class MyGame final : public Application
    {
        public:
            MyGame()
            {
                // @todo: Use a filesystem lib to parse filenames
                SetSceneYaml("/home/sam/Game/Neon/build/assets/game.yaml");
            }

            [[nodiscard]] bool Initialize()
            {
                return Application::Initialize(800, 600, "Neon Void (0.0.4)");
            }
    };
}
