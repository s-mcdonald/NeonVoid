
#pragma once

#include <Runtime/Entity/Entity.hpp>
#include "../Mankind.hpp"

namespace Neon
{
    class ControllablePlayerEntity final : public Entity
    {
        public:
            ControllablePlayerEntity(): Entity(ENTITY_ID_MAIN_PLAYER) {};
            ControllablePlayerEntity(const std::initializer_list<Component*> components)
                : Entity(ENTITY_ID_MAIN_PLAYER, components) {};

            ~ControllablePlayerEntity() override = default;

            void OnInit() override;
            void OnUpdate() override;
            void OnDestroy() override;
    };
}
