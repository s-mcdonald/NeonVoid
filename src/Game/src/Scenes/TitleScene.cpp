/**
 * {SourceHeader}
 */

#include <NeonEngine/All.hpp>

#include <Runtime/ExtRuntime.hpp>

#include "../Entities/MoveablePlayerEntity.hpp"
#include "TitleScene.hpp"

namespace Neon
{
    constexpr uint8_t MAIN_PLAYER = 1;

    TitleScene::TitleScene(const SceneType type)
        : Scene(type)
    {
        auto& runtimeApi = RuntimeApi::GetInstance();

        // Load All Shaders
        // runtimeApi.LoadShaderPair
        // (
        //     "id.white_circle",
        //     "/home/sam/Game/Neon/src/Game/assets/shaders/WhiteCircle/shader.vert",
        //     "/home/sam/Game/Neon/src/Game/assets/shaders/WhiteCircle/shader.frag"
        // );


        /// Audio - Intro Sound
        auto* introMusic = new AudioComponent("./assets/audio/neon_void_intro.mp3");
        AddComponent("aud.intro", introMusic);

        ///
        /// White Circle
        ///
        std::vector<float> circle_vertices = runtimeApi.GenerateCircleVertices(1.0f, 100);


        auto circle_shader = runtimeApi.CreateShader(
            "/home/sam/Game/Neon/src/Game/assets/shaders/WhiteCircle/shader.vert",
            "/home/sam/Game/Neon/src/Game/assets/shaders/WhiteCircle/shader.frag"
        );

        auto* circle_component = new ShaderComponent(circle_vertices, circle_shader);
        AddComponent("vao.circle", circle_component);

        auto* mainPlayer = new MoveablePlayerEntity();
        m_entities[mainPlayer->GetId()] = mainPlayer;
    }

    void TitleScene::OnInit()
    {
#if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
        std::cout << "<GAME> TitleScene::OnInit\n";
#endif

        // Need to give config to AudioComponents so the comp
        // knows when and how to start playing.
        if (auto* x = GetComponent("aud.intro"))
        {
            auto* ac = dynamic_cast<AudioComponent*>(x);
            ac->TriggerPlayOnce();
        }
    }

    void TitleScene::OnUpdate()
    {
        // ..
    }
}
