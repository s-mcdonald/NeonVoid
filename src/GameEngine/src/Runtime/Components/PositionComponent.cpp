/**
 * 
 */
#include <iostream>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    PositionComponent::PositionComponent(float x = 0.0f, float y = 0.0f) : x(x), y(y) 
        : Component()
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "PositionComponent::Constructor called\n";
        #endif
    }

    PositionComponent::~PositionComponent() 
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "PositionComponent::Destructor completed\n";
        #endif
    }
}
