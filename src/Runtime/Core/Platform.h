/**
 * 
 */
#pragma once

#include "Game/Game.h"

namespace Neon 
{
    class Platform 
    {
        public:
            Platform();
            virtual ~Platform();
    
            virtual bool Initialize(int width, int height, const char* title);

            virtual void Run(Game* game);
            
        protected:
            virtual void CleanResources();
        };
}
