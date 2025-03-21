/**
 * 
 */
#include <iostream>

#include "Game/GameState.h"

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

    bool GameState::IsLoading()
    {
        return true;
    }

    bool GameState::IsMenuScene()
    {
        return false;
    }

    bool GameState::IsGamePlayScene()
    {
        return false;
    }

    void GameState::LoadLoading() 
    {
        // ..
    }

    void GameState::LoadMenuScene()
    {
        // ..
    }

    void GameState::LoadGamePlayScene(int level) 
    {
        // ..
    }
}
