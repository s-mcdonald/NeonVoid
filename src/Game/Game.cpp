/**
 * 
 */
#include <iostream>

#include "Game.h"

namespace Neon 
{
    Game::Game()
    {
        std::cout << "Game::Constructor called\n";
    }

    Game::~Game() 
    {
        std::cout << "Game::Destructor called\n";
    }
}
