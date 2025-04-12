/**
 * 
 */
#include <iostream>

#include <Runtime/Runtime.hpp>
#include <Runtime/Components/Components.hpp>
#include <Runtime/Input/Input.hpp>

namespace Neon 
{
    void ControllerComponent::HandleInput(Input* input)
    {
        constexpr  float directionUp = -10.0f;
        constexpr  float directionLeft = -10.0f;
        constexpr  float directionRight = 10.0f;
        constexpr  float directionDown = 10.0f;

        constexpr  float targetFps = 60.0f;

        constexpr float deltaTime = 1.0f / targetFps;

        // check if KeyboardInput
        if (const auto* x = dynamic_cast<KeyboardInput*>(input))
        {
            if (x->IsKeyPressed(Key::Up))
            {
                m_accelerationY = deltaTime * directionUp;
            }
            else if (x->IsKeyPressed(Key::Down))
            {
                m_accelerationY = deltaTime * directionDown;
            }

            if (x->IsKeyPressed(Key::Left))
            {
                m_accelerationX = deltaTime * directionLeft;
            }
            else if (x->IsKeyPressed(Key::Right))
            {
                m_accelerationX = deltaTime * directionRight;
            }
        }
    }

    void ControllerComponent::Update(float deltaTime)
    {
        // ...
    }
}
