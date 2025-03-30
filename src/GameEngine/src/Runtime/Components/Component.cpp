/**
 * 
 */
#include <iostream>
#include <cmath>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    Component::Component() 
        : IComponent()
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "Component::Constructor called\n";
        #endif
    }

    // @todo: Abstract this to platforms
    Component::~Component() 
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "Component::Destructor completed\n";
        #endif
    }

    void Component::OnInit() 
    {
        //
    }

    void Component::OnUpdate() 
    {
        //
    }
}
