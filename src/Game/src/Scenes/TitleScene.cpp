/**
 * 
 */
#include <iostream>
#include <cmath>

#include "../../GameEngine/src/Runtime/Runtime.hpp"
#include "TitleScene.hpp"

namespace Neon
{
    constexpr uint8_t MAIN_PLAYER = 1;

    TitleScene::TitleScene(const SceneType type)
        : Scene(type)
    {
        std::vector<float> vertices = {
            0.0f,  0.5f,   // Top vertex
           -0.5f, -0.5f,   // Bottom left vertex
            0.5f, -0.5f    // Bottom right vertex
        };
        auto* component = new QuadComponent(vertices); // LoadShaderGSL('triangle'));
        AddComponent("vao.triangle", component);

        // Add Audio
        auto* introMusic = new AudioComponent("./assets/audio/neon_void_intro.mp3");
        AddComponent("aud.intro", introMusic);
    }

    void TitleScene::OnInit()
    {
        std::cout << "Child \n";

        // Need to give config to AudioComponents so the comp
        // knows when and how to start playing..
        if (auto* x = GetComponent("aud.intro"))
        {
            auto* ac = dynamic_cast<AudioComponent*>(x);
            ac->TriggerPlayOnce();
        }
    }

    void TitleScene::OnUpdate()
    {
        // later we will control entities from here
    }
}
