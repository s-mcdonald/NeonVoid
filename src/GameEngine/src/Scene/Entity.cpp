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

#include <NeonEngine/Entity.hpp>

namespace Neon
{
    Entity::Entity(const EntityID id, const std::initializer_list<Component*> components)
        : m_id(id)
    {
        for (auto* component : components)
        {
            AddComponent(component);
        }
    }

    Entity::~Entity()
    {
        for (auto& [_, component] : m_components)
        {
            delete component;
        }
    }

    void Entity::OnInit()
    {
        for (const auto& [_, component] : m_components)
        {
            component->OnInit();
        }
    }

    void Entity::OnUpdate()
    {
        for (const auto& [_, component] : m_components)
        {
            component->OnUpdate();
        }
    }

    void Entity::OnRender()
    {
        for (const auto& [_, component] : m_components)
        {
            component->OnRender();
        }
    }

    void Entity::AddComponent(Component* component)
    {
        component->SetParentEntity(this);

        auto type = std::type_index(typeid(*component));
        if (m_components.contains(type))
        {
            delete m_components[type];
        }

        m_components[type] = component;
    }

    void Entity::HandleInput(Input* input)
    {
        auto* movementComponent = GetComponent<MovementComponent>();
        if (movementComponent)
        {
            movementComponent->HandleInput(input);
        }
    }

    EntityID Entity::GetId() const
    {
        return m_id; 
    }
}
