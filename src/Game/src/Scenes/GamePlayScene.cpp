/**
 * {SourceHeader}
 */

#include <iostream>

#include <Runtime/Runtime.hpp>
#include "GamePlayScene.hpp"

namespace Neon
{
    constexpr uint8_t MAIN_PLAYER = 1;

    GamePlayScene::GamePlayScene(const SceneType type)
        : Scene(type)
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
