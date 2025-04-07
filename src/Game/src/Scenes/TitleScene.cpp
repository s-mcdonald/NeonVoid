/**
 * 
 */
#include <cmath>
#include <iostream>

#include "TitleScene.hpp"
#include "../../GameEngine/src/Runtime/Runtime.hpp"
#include "../../GameEngine/src/Runtime/Engine/Shader.hpp"

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
        /// Green Triangle
        ///
        std::vector<float> vertices = {
            0.0f,  0.5f,   // Top vertex
           -0.5f, -0.5f,   // Bottom left vertex
            0.5f, -0.5f    // Bottom right vertex
        };

        auto shader = new Shader(
            "/home/sam/Game/Neon/src/Game/assets/shaders/GreenTriangle/shader.vert",
            "/home/sam/Game/Neon/src/Game/assets/shaders/GreenTriangle/shader.frag"
        );

        auto* component = new QuadComponent(vertices, shader);
        AddComponent("vao.triangle", component);

        ///
        /// White Circle
        ///
        std::vector<float> circle_vertices = OpenGL::GenerateCircleVertices(1.0f, 100);

        auto circle_shader = new Shader(
            "/home/sam/Game/Neon/src/Game/assets/shaders/WhiteCircle/shader.vert",
            "/home/sam/Game/Neon/src/Game/assets/shaders/WhiteCircle/shader.frag"
        );

        auto* circle_component = new CircleComponent(circle_vertices, circle_shader);
        AddComponent("vao.circle", circle_component);
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
