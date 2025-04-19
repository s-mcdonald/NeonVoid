/**
 * {SourceHeader}
 */

#pragma once

#include <NeonEngine/All.hpp>

namespace Neon
{
    class MyGame final : public Application
    {
        public:
            MyGame()
            {
                // @todo: Use a filesystem lib to parse filenames
                SetSceneYaml("./assets/game.yaml");
            }

            [[nodiscard]] bool Initialize()
            {
                return Application::Initialize(800, 600, "Neon Void (0.0.5)");
            }
    };
}
