/**
 * {SourceHeader}
 */

#include <iostream>

#include <Runtime/ExtRuntime.hpp>

#include <NeonEngine/Components/Components.hpp>
#include <NeonEngine/GameEngine.hpp>
#include "MoveablePlayerEntity.hpp"

namespace Neon
{
    void MoveablePlayerEntity::OnInit()
    {
        /// Green Triangle
        std::vector<float> vertices = {
            0.0f,  0.5f,   // Top vertex
           -0.5f, -0.5f,   // Bottom left vertex
            0.5f, -0.5f    // Bottom right vertex
        };

        auto shader = GameEngineApi::GetInstance().CreateShader(
            "/home/sam/Game/Neon/src/Game/assets/shaders/GreenTriangle/shader.vert",
            "/home/sam/Game/Neon/src/Game/assets/shaders/GreenTriangle/shader.frag"
        );

        auto* component = new ShaderComponent(vertices, shader);
        AddComponent(component);

        auto* positionComponent = new PositionComponent(0.0f, 0.0f);
        AddComponent(positionComponent);

        auto* movementComponent = new MovementComponent();
        movementComponent->AllowMovementOf(positionComponent); // change to using events instead
        AddComponent(movementComponent);

        Entity::OnInit();
    }

    void MoveablePlayerEntity::OnUpdate()
    {;
#if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
        std::cout << "ControllablePlayerEntity::OnUpdate()" << std::endl;
#endif

        Entity::OnUpdate();
    }

    void MoveablePlayerEntity::OnDestroy()
    {
#if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
        std::cout << "ControllablePlayerEntity::OnDestroy()" << std::endl;
#endif
    }
}