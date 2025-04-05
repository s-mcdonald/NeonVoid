/**
 *
 */

#pragma once

#include "../../GameEngine/src/Runtime/Runtime.hpp"

namespace Neon
{
    class MyGame final : public Game
    {
        public:
            MyGame();
            [[nodiscard]] bool Initialize() const;
    };

}
