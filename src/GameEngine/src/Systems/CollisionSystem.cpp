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

#include <NeonEngine/CollisionSystem.hpp>
#include <NeonEngine/Components.hpp>
#include <NeonEngine/Entity.hpp>

namespace Neon
{
    void CollisionSystem::RegisterEntity(Entity* entity)
    {
        m_entities.push_back(entity);
    }

    bool CollisionSystem::AABBCollision(
        const CollisionComponent& aC,
        const PositionComponent& aP,
        const CollisionComponent& bC,
        const PositionComponent& bP
        )
    {
        return (aP.GetPoint().x < bP.GetPoint().x + bC.GetWidth() &&
                aP.GetPoint().x + aC.GetWidth() > bP.GetPoint().x &&
                aP.GetPoint().y < bP.GetPoint().y + bC.GetHeight() &&
                aP.GetPoint().y + aC.GetHeight() > bP.GetPoint().y);
    }

    void CollisionSystem::OnUpdate()
    {
        for (size_t i = 0; i < m_entities.size(); ++i)
        {
            for (size_t j = i + 1; j < m_entities.size(); ++j)
            {
                CheckCollision(m_entities[i], m_entities[j]);
            }
        }
    }

    void CollisionSystem::CheckCollision(Entity* a, Entity* b)
    {
        auto* collisionA = a->GetComponent<CollisionComponent>();
        auto* collisionB = b->GetComponent<CollisionComponent>();

        if (collisionA == nullptr || collisionB == nullptr)
        {
            return;
        }

        auto* collisionAP = a->GetComponent<PositionComponent>();
        auto* collisionBP = b->GetComponent<PositionComponent>();

        if (collisionA && collisionB && AABBCollision(
            *collisionA,
            *collisionAP,
            *collisionB,
            *collisionBP
            ))
        {
            // @todo: if there is a collision, then trigger the comp OnCollision
            collisionA->OnCollision(b);
            collisionB->OnCollision(a);
        }
    }
}
