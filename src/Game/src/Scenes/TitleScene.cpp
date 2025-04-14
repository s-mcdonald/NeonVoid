/**
 * {SourceHeader}
 */

#include <cmath>
#include <iostream>

#include <../../../GameEngine/src/Runtime/Runtime/Backends/Shader.hpp>
#include <Runtime/Components/Components.hpp>
#include <Runtime/Runtime.hpp>
#include <Runtime/Runtime/Backends/OpenGL/OpenGL.hpp>
#include "TitleScene.hpp"
#include <Runtime/Runtime/Backends/OpenGL/OpenGLShader.hpp>

#include "../Entities/MoveablePlayerEntity.hpp"

namespace Neon
{
    constexpr uint8_t MAIN_PLAYER = 1;

    TitleScene::TitleScene(const SceneType type)
        : Scene(type)
    {
        ///
        /// Audio - Intro Sound
        ///
        auto* introMusic = new AudioComponent("./assets/audio/neon_void_intro.mp3");
        AddComponent("aud.intro", introMusic);

        ///
        /// White Circle
        ///
        std::vector<float> circle_vertices = OpenGL::GenerateCircleVertices(1.0f, 100);

        auto circle_shader = new OpenGLShader(
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
        // knows when and how to start playing..
        if (auto* x = GetComponent("aud.intro"))
        {
            auto* ac = dynamic_cast<AudioComponent*>(x);
            ac->TriggerPlayOnce();
        }
    }

    void TitleScene::OnUpdate()
    {
        // Component* triangle = GetComponent("vao.triangle");
        //
        // if (auto* shaderComponent = dynamic_cast<ShaderComponent*>(triangle))
        // {
        //     std::vector<float> vertices = {
        //         1.0f,  0.5f,   // Top vertex
        //        -0.5f, -0.5f,   // Bottom left vertex
        //         1.5f, -0.5f    // Bottom right vertex
        //     };
        //
        //     shaderComponent->UpdateData(vertices);
        // }
    }
}
