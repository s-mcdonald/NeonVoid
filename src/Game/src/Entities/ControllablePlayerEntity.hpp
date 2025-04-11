
#pragma once

#include <Runtime/Entity/Entity.hpp>

namespace Neon
{
    class ControllablePlayerEntity final : public Entity
    {
        public:
            ControllablePlayerEntity(): Entity(1) {};
            ControllablePlayerEntity(const std::initializer_list<Component*> components)
                : Entity(1, components) {};

            ~ControllablePlayerEntity() override = default;

            void OnInit() override;
            void OnUpdate() override;
            void OnDestroy() override;
    };
}
