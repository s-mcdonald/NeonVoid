
#include <iostream>

#include <Runtime/Components/Components.hpp>
#include "ControllablePlayerEntity.hpp"

namespace Neon
{
    void ControllablePlayerEntity::OnInit()
    {
        ///
        /// Green Triangle
        ///
        std::vector<float> vertices = {
            0.0f,  0.5f,   // Top vertex
           -0.5f, -0.5f,   // Bottom left vertex
            0.5f, -0.5f    // Bottom right vertex
        };

        auto shader = new Shader(
            "/home/sam/Game/Neon/src/Game/assets/shaders/GreenTriangle/shader.vert",
            "/home/sam/Game/Neon/src/Game/assets/shaders/GreenTriangle/shader.frag"
        );

        auto* component = new ShaderComponent(vertices, shader);
        AddComponent(component);

        auto* positionComponent = new PositionComponent(0.0f, 0.0f);

        auto* movementComponent = new MovementComponent();
        movementComponent->AllowMovementOf(positionComponent);
        AddComponent(movementComponent);

        Entity::OnInit();
    }

    void ControllablePlayerEntity::OnUpdate()
    {;
        // #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
        //         std::cout << "ControllablePlayerEntity::OnUpdate()" << std::endl;
        // #endif
        Entity::OnUpdate();
    }

    void ControllablePlayerEntity::OnDestroy()
    {
#if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
        std::cout << "ControllablePlayerEntity::OnDestroy()" << std::endl;
#endif
    }
}