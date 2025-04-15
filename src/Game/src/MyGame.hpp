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
            MyGame();
            [[nodiscard]] bool Initialize() const;
    };
}
