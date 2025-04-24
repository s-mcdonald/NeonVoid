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
    Entity::~Entity()
    {
        if (false == m_destroyed)
        {
            Entity::OnDestroy();
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

    void Entity::OnDestroy()
    {
        if (m_destroyed)
        {
            return;
        }

        std::vector<std::type_index> keysToDelete;
        for (const auto& [type, component] : m_components)
        {
            if (component != nullptr)
            {
                delete component;
            }
            keysToDelete.push_back(type);
        }

        for (auto& key : keysToDelete)
        {
            m_components.erase(key);
        }

        m_destroyed = true;
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
