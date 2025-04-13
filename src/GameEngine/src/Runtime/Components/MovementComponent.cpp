/**
 * {SourceHeader}
 */

#include <iostream>

#include <Runtime/Components/Components.hpp>
#include <Runtime/Runtime.hpp>
#include <Runtime/Runtime/Input.hpp>
#include <Runtime/Types.hpp>

namespace Neon 
{
    void MovementComponent::HandleInput(OpenGLInput* input)
    {
        // check if KeyboardInput
        if (auto* x = dynamic_cast<KeyboardInput*>(input))
        {
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

    // @todo: we need to fire events instead of tightly bound object here
    void MovementComponent::AllowMovementOf(PositionComponent* component)
    {
        mx_positionalComponents.emplace_back(component);
    }

    // @todo: we need to fire events instead of tightly bound object here
    void MovementComponent::OnUpdate()
    {
        for (auto* component : mx_positionalComponents)
        {
            Point x = component->GetPoint();

            // #ifdef NEON_DEBUG_KB_INPUT
            //         std::cout << "[DEBUG](Keyboard) OLD: x: " << x.x << " y: " << x.y << "\n";
            // #endif

            x.y += m_directionY;
            x.x += m_directionX;

            // #ifdef NEON_DEBUG_KB_INPUT
            //      std::cout << "[DEBUG](Keyboard) NEW: x: " << x.x << " y: " << x.y << "\n";
            // #endif

            component->UpdateData(x);
        }
    }
}
