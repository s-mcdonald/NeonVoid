/**
 *    ███╗   ██╗███████╗ ██████╗ ███╗   ██╗
 *    ████╗  ██║██╔════╝██╔═══██╗████╗  ██║
 *    ██╔██╗ ██║█████╗  ██║   ██║██╔██╗ ██║
 *    ██║╚██╗██║██╔══╝  ██║   ██║██║╚██╗██║
 *    ██║ ╚████║███████╗╚██████╔╝██║ ╚████║
 *    ╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═══╝
 * ========================================
 * NeonVoid Engine
 * 2D Game Engine in C++
 * ----------------------------------------
 * Copyright (c) 2024 Sam McDonald
 * Repository: https://github.com/s-mcdonald/NeonVoid
 */

#include <iostream>
#include <algorithm>

#include <NeonEngine/Components.hpp>
#include <NeonEngine/Entity.hpp>

namespace Neon 
{
    void MovementComponent::HandleInput(Input* input)
    {
        if (auto* x = dynamic_cast<KeyboardInput*>(input))
        {
            if (x->IsKeyPressed(Key::Up))
            {
                m_directionY = deltaTime * DirectionDeltaUp;
            }
            else if (x->IsKeyPressed(Key::Down))
            {
                m_directionY = deltaTime * DirectionDeltaDown;
            }
            else
            {
                if (m_directionY > 0)
                {
                    m_directionY = std::max(0.0f, m_directionY - Deceleration);
                }
                else if (m_directionY < 0)
                {
                    m_directionY = std::min(0.0f, m_directionY + Deceleration);
                }
            }

            if (x->IsKeyPressed(Key::Left))
            {
                m_directionX = deltaTime * DirectionDeltaLeft;
            }
            else if (x->IsKeyPressed(Key::Right))
            {
                m_directionX = deltaTime * DirectionDeltaRight;
            }
            else
            {
                if (m_directionX > 0)
                {
                    m_directionX = std::max(0.0f, m_directionX - Deceleration);
                }
                else if (m_directionX < 0)
                {
                    m_directionX = std::min(0.0f, m_directionX + Deceleration);
                }
            }

            m_directionX = std::clamp(m_directionX, -MaxSpeed, MaxSpeed);
            m_directionY = std::clamp(m_directionY, -MaxSpeed, MaxSpeed);
        }
    }

    // @todo: we need to fire events instead of tightly bound object here
    void MovementComponent::OnUpdate()
    {
        auto* parent = GetParentEntity();

        if (parent == nullptr)
        {
            return;
        }

        auto* component = parent->GetComponent<PositionComponent>();

        if (component == nullptr)
        {
            return;
        }

        Point p = component->GetPoint();

        p.x += m_directionX;
        if (p.x > MaxSpeed) p.x = MaxSpeed;
        if (p.x < -MaxSpeed) p.x = -MaxSpeed;

        p.y += m_directionY;
        if (p.y > MaxSpeed) p.y = MaxSpeed;
        if (p.y < -MaxSpeed) p.y = -MaxSpeed;

        component->UpdateData(p);
    }
}
