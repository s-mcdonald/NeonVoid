/**
 * {SourceHeader}
 */

#pragma once

#include <NeonEngine/Entity/Entity.hpp>
#include "../Mankind.hpp"

namespace Neon
{
    class MoveablePlayerEntity final : public Entity
    {
        public:
            MoveablePlayerEntity(): Entity(ENTITY_ID_MAIN_PLAYER) {};
            MoveablePlayerEntity(const std::initializer_list<Component*> components)
                : Entity(ENTITY_ID_MAIN_PLAYER, components) {};

            ~MoveablePlayerEntity() override = default;

            void OnInit() override;
            void OnUpdate() override;
            void OnDestroy() override;
    };
}
