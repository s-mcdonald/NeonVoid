/**
 * 
 */
#include <iostream>
#include <cmath>

#include "../../GameEngine/src/Runtime/Runtime.hpp"
#include "Scenes.hpp"

namespace Neon
{
    constexpr uint8_t MAIN_PLAYER = 1;

    TitleScene::TitleScene(const SceneType type, Platform* platform)
        : Scene(type, platform)
    {
        // Add Quad / triangle
        auto* component = new QuadComponent();
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


    GamePlayScene::GamePlayScene(const SceneType type, Platform* platform)
        : Scene(type, platform)
    {
        // Add Text
        auto* titleText = new TextComponent("Neon Void: A Saga", 16);
        AddComponent("text.title", titleText);
    }

    void GamePlayScene::OnInit()
    {
        std::cout << "GamePlayScene::OnInit \n";
    }

    void GamePlayScene::OnUpdate()
    {
        std::cout << "GamePlayScene::OnUpdate \n";
    }
}
