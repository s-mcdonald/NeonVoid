/**
 * 
 */
#include <iostream>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    PositionComponent::PositionComponent(const float x = 0.0f, const float y = 0.0f)
        : Component()
        , m_position(x,y)
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "PositionComponent::Constructor called\n";
        #endif
    }

    void PositionComponent::OnDestroy()
    {
        // ....
    }

    Point PositionComponent::GetPoint() const
    {
        return m_position;
    }
}
