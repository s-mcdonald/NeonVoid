/**
 *
 */

#include <iostream>

#include "Runtime/Runtime.hpp"

#include "Game/NeonFunctions.hpp"

void Neon::LoadGameData(Game* game, GameEngine& gameEngine)
{
    using namespace Neon;
    {
        std::cout << "Entry ==> LoadGameData(game)\n";

        Scene* onlyScene = new Scene(gameEngine.GetPlatform());
        game->AddScene(onlyScene);

        Component* component = new Component();

        component->SetInitFunction([]() {
            std::cout << "Initializing component...\n";
        });
    
        component->SetRenderFunction([]() {
            std::cout << "Rendering component...\n";
        });
    
        component->SetVertices({0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f});

        // Now we need to add component to scene!
    }
}
