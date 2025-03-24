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

        Scene* scene = new Scene(gameEngine.GetPlatform());
        game->AddScene(scene);

        Component* component = new Component();

        component->SetInitFunction([]() {
            std::cout << "Initializing component...\n";
        });
    
        component->SetRenderFunction([]() {
            std::cout << "Rendering component...\n";
        });       

        // Now we need to add component to scene!
        scene->AddComponent(component);
    }
}
