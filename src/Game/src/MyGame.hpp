/**
 * {SourceHeader}
 */

#pragma once

#include <NeonEngine/Application.hpp>
#include <NeonEngine/NeonEngine.hpp>

namespace Neon
{
    class MyGame final : public Application
    {
        public:
            MyGame();
            [[nodiscard]] bool Initialize() const;
    };
}
