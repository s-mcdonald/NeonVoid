/**
 * 
 */
#include <iostream>

#include <Runtime/Components/Components.hpp>
#include <Runtime/Input/Input.hpp>
#include <Runtime/Runtime.hpp>

namespace Neon 
{
    void MovementComponent::HandleInput(OpenGLInput* input)
    {
        // @todo: move these const to Inout potentially or types hpp
        constexpr float directionUp = -10.0f;
        constexpr float directionLeft = -10.0f;
        constexpr float directionRight = 10.0f;
        constexpr float directionDown = 10.0f;

        constexpr float targetFps = 60.0f;

        constexpr float deltaTime = 1.0f / targetFps;

        // check if KeyboardInput
        if (auto* x = dynamic_cast<KeyboardInput*>(input))
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

    void MovementComponent::AllowMovementOf(PositionComponent* component)
    {
        mx_positionalComponents.emplace_back(component);
    }

    void MovementComponent::OnUpdate()
    {
        for (auto* component : mx_positionalComponents)
        {
            component->OnUpdate();
        }
    }
}
