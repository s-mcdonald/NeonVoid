/**
 * {SourceHeader}
 */

#pragma once

#include <Runtime/Runtime.hpp>
#include <Runtime/Application.hpp>

namespace Neon
{
    class MyGame final : public Application
    {
        public:
            MyGame();
            [[nodiscard]] bool Initialize() const;
    };
}
