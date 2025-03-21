/**
 *
 */

#pragma once

#include "Game/Scene.h"
#include "Game/GameState.h"

namespace Neon 
{
    class Game
    {
        public:
            Game();
            ~Game();

        public:
            void AddScene(Scene* scene);

            Scene* GetCurrentScene();

        private:
            GameState* m_gameState{nullptr};    
            Scene* m_onlyScene{nullptr};
    };
}
