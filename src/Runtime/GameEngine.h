#pragma once

#include "Runtime/Core/Platform.h"

namespace Neon 
{
    class GameEngine
    {
        public:
            GameEngine();
            ~GameEngine();

        public:
            bool Initialize(int width, int height, const char* title);

            void Run(Game* game);   

        protected:            
            void CleanResources();

        private:
            Platform* m_platform;
    };
}
