/**
 * {SourceHeader}
 */

#pragma once

#include <Runtime/Runtime.hpp>
#include <Runtime/Game.hpp>

namespace Neon
{
    class MyGame final : public Game
    {
        public:
            MyGame();
            [[nodiscard]] bool Initialize() const;
    };
}
