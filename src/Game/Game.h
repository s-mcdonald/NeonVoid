/**
 *
 */

#pragma once

#include "Game/Scene.h"

namespace Neon 
{
    class Game
    {
        public:
            Game();
            ~Game();

        public:
            void AddScene(Scene* scene);

        private:
            Scene* m_onlyScene{nullptr};
    };
}
