/**
 *
 */

#pragma once

namespace Neon 
{
    class GameState
    {
        public:
            GameState();
            ~GameState();
        
        public:
            bool IsLoading();                   // Query these as much as you want
            bool IsMenuScene();                 // Query these as much as you want
            bool IsGamePlayScene();             // Query these as much as you want
            
            void LoadLoading();                 // The load command will immediately load the new scene/menu or whatever, if you
            void LoadMenuScene();               // call the same Scene, it should not reload it.
            void LoadGamePlayScene(int level);
    };
}
