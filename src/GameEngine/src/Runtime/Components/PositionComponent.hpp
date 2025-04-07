#pragma once

#include <Runtime/Runtime.hpp>

namespace Neon
{
    class PositionComponent : public Component
    {
        public:
            explicit PositionComponent(float, float);
            void OnDestroy() override;
            [[nodiscard]] Point GetPoint() const;

        private:
            Point m_position;
    };
}
