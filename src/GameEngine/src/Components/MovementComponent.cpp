/**
 *    ███╗   ██╗███████╗ ██████╗ ███╗   ██╗
 *    ████╗  ██║██╔════╝██╔═══██╗████╗  ██║
 *    ██╔██╗ ██║█████╗  ██║   ██║██╔██╗ ██║
 *    ██║╚██╗██║██╔══╝  ██║   ██║██║╚██╗██║
 *    ██║ ╚████║███████╗╚██████╔╝██║ ╚████║
 *    ╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═══╝
 * ========================================
 *                 NeonVoid
 *         A 2D Game Engine in C++
 * ----------------------------------------
 * License: MIT
 * Copyright (c) : 2024 Sam McDonald
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
            m_directionInput = glm::vec2(0.0f, 0.0f);

            if (x->IsKeyPressed(Key::Up)) m_directionInput.y += DirectionDeltaUp;
            if (x->IsKeyPressed(Key::Down)) m_directionInput.y += DirectionDeltaDown;
            if (x->IsKeyPressed(Key::Left)) m_directionInput.x += DirectionDeltaLeft;
            if (x->IsKeyPressed(Key::Right)) m_directionInput.x += DirectionDeltaRight;

            // prevent diagonal speed-up
            if (m_directionInput.x != 0.0f || m_directionInput.y != 0.0f)
            {
                m_directionInput = glm::normalize(m_directionInput);
                m_velocity += m_directionInput * NV_Acceleration * deltaTime;
            }
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

        // No input change, apply gravity and friction will
        // sump movement in general. Gravity being
        // the downward force.
        if (glm::length(m_directionInput) == 0.0f)
        {
            m_velocity *= (NV_FULL_Velocity - NV_Friction * deltaTime);
            if (glm::length(m_velocity) < NV_MIN_Velocity)
            {
                m_velocity = glm::vec2(NV_ZERO_Velocity);
            }
        }

        // Clamp velocity to max speed
        if (glm::length(m_velocity) > NV_MAX_Velocity)
        {
            m_velocity = glm::normalize(m_velocity) * NV_MAX_Velocity;
        }

        // Update the position based on velocity
        p.x += m_velocity.x;
        p.y += m_velocity.y;

        // Clamp position to bounds
        const float bounds = component->GetBounds();
        p.x = std::clamp(p.x, -bounds, bounds);
        p.y = std::clamp(p.y, -bounds, bounds);

        component->SetPoint(p);
    }
}
