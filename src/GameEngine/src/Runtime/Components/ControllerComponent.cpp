/**
 * 
 */
#include <iostream>

#include <Runtime/Runtime.hpp>
#include <Runtime/Components/Components.hpp>
#include <Runtime/Input/Input.hpp>

namespace Neon 
{
    void ControllerComponent::HandleInput(const Input& input)
    {
        const float directionUp = -10.0f;
        const float directionLeft = -10.0f;
        const float directionRight = 10.0f;
        const float directionDown = 10.0f;

        const float targetFps = 60.0f;

        const float deltaTime = 1.0f / targetFps;

        if (input.IsKeyPressed(Key::Up))
        {
            m_accelerationY = deltaTime * directionUp;
        }
        else if (input.IsKeyPressed(Key::Down))
        {
            m_accelerationY = deltaTime * directionDown;
        }

        if (input.IsKeyPressed(Key::Left))
        {
            m_accelerationX = deltaTime * directionLeft;
        }
        else if (input.IsKeyPressed(Key::Right))
        {
            m_accelerationX = deltaTime * directionRight;
        }
    }

    void ControllerComponent::Update(float deltaTime)
    {
        // ...
    }
}
