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
                #ifdef NEON_DEBUG_KB_INPUT
                    std::cout << "[DEBUG][KeyInput] : Up" << "\n";
                #endif

                m_directionY = deltaTime * DirectionDeltaUp;
            }
            else if (x->IsKeyPressed(Key::Down))
            {
                #ifdef NEON_DEBUG_KB_INPUT
                    std::cout << "[DEBUG][KeyInput] : Down" << "\n";
                #endif
                m_directionY = deltaTime * DirectionDeltaDown;
            }

            if (x->IsKeyPressed(Key::Left))
            {
                #ifdef NEON_DEBUG_KB_INPUT
                    std::cout << "[DEBUG][KeyInput] : Left" << "\n";
                #endif
                m_directionX = deltaTime * DirectionDeltaLeft;
            }
            else if (x->IsKeyPressed(Key::Right))
            {
                #ifdef NEON_DEBUG_KB_INPUT
                    std::cout << "[DEBUG][KeyInput] : Right" << "\n";
                #endif
                m_directionX = deltaTime * DirectionDeltaRight;
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
            Point x = component->GetPoint();
            x.y += m_accelerationY;
            x.x += m_accelerationX;
            component->UpdateData(x);
        }
    }
}
