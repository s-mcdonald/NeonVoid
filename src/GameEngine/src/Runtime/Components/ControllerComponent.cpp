/**
 * 
 */
#include <iostream>

#include <Runtime/Runtime.hpp>
#include <Runtime/Components/Components.hpp>
#include <Runtime/Input/Input.hpp>

namespace Neon 
{
    // Change the class name to MovementComponent
    void ControllerComponent::HandleInput(Input* input)
    {
        // @todo: move these const to Inout potentially or types hpp
        constexpr float directionUp = -10.0f;
        constexpr float directionLeft = -10.0f;
        constexpr float directionRight = 10.0f;
        constexpr float directionDown = 10.0f;

        constexpr float targetFps = 60.0f;

        constexpr float deltaTime = 1.0f / targetFps;

        // check if KeyboardInput
        if (const auto* x = dynamic_cast<KeyboardInput*>(input))
        {
            std::cout << "KeyboardInput\n";
            std::cout << "Checking for Input\n";

            if (x->IsKeyPressed(Key::Up))
            {
                std::cout << "Up\n";
                m_accelerationY = deltaTime * directionUp;
            }
            else if (x->IsKeyPressed(Key::Down))
            {
                std::cout << "Down\n";
                m_accelerationY = deltaTime * directionDown;
            }

            if (x->IsKeyPressed(Key::Left))
            {
                std::cout << "Left\n";
                m_accelerationX = deltaTime * directionLeft;
            }
            else if (x->IsKeyPressed(Key::Right))
            {
                std::cout << "Right\n";
                m_accelerationX = deltaTime * directionRight;
            }
        }
    }

    void ControllerComponent::Update(float deltaTime)
    {
        // ...
    }
}
