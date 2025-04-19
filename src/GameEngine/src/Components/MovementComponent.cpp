/**
 * {SourceHeader}
 */

#include <iostream>

#include <NeonEngine/Components.hpp>
#include <NeonEngine/Entity.hpp>

namespace Neon 
{
    void MovementComponent::HandleInput(Input* input)
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
    void MovementComponent::OnUpdate()
    {
        auto* parent = GetParentEntity();

        // if (parent == nullptr)
        // {
        //     return;
        // }

        auto* component = parent->GetComponent<PositionComponent>();

        if (component == nullptr)
        {
            return;
        }

        Point p = component->GetPoint();

        std::cout << "[DEBUG][Movement] : " << m_directionY << "\n";
        std::cout << "[DEBUG][Movement] : " << m_directionX << "\n";
        std::cout << "[DEBUG][Movement] : " << p.x << " " << p.y << "\n";

        p.y += m_directionY;
        p.x += m_directionX;

        component->UpdateData(p);
    }
}
