/**
 * 
 */
#include <iostream>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    GameState::GameState()
    {
        std::cout << "GameState::Constructor called\n";
    }

    GameState::~GameState() 
    {
        std::cout << "GameState::Destructor called\n";
    }
}
