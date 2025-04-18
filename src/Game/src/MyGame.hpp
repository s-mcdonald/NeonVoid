/**
 * {SourceHeader}
 */

#pragma once


/////
///// GOAL: Make Game project an empty clean project for new devs to use
///// Make sandbox where we can dev and experiment.
///// On build, sandbox app will compile.
///// This is better because the Game/ folder is always ready to go
/////

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
