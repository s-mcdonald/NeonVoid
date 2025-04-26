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

#pragma once

#include <NeonEngine/Types.hpp>
#include <NeonEngine/Components.hpp>

namespace Neon
{
    class CollisionSystem
    {
        public:
            CollisionSystem() = default;
            ~CollisionSystem()
            {
                m_entities.empty();
            };
            void RegisterEntity(Entity* entity);
            void DeregisterEntity(Entity* entity);
            static bool AABBCollision(
                const CollisionComponent& aC,
                const PositionComponent& aP,
                const CollisionComponent& bC,
                const PositionComponent& bP
                );
            void OnUpdate();

        private:
            void CheckCollision(Entity* a, Entity* b);
            std::vector<Entity*> m_entities;
    };
}

