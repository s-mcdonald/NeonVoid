/**
 * 
 */
#include <Runtime/Runtime.hpp>
#include <Runtime/Entity/Entity.hpp>

namespace Neon
{
    Entity::Entity(const EntityID id, const std::initializer_list<Component*> components)
        : m_id(id)
    {
        for (auto& component : components)
        {
            m_components.emplace_back(component);
        }
    }

    Entity::~Entity()
    {
        for (const auto* c : m_components)
        {
            delete c;
        }
    }

    template <typename T>
    void Entity::AddComponent(Component* component)
    {
        m_components.emplace_back(component);
    }

    EntityID Entity::GetId() const
    {
        return m_id; 
    }
}