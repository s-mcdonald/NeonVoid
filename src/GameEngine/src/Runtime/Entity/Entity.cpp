/**
 * 
 */
#include "Runtime/Runtime.hpp"

#include "Entity.hpp"

namespace Neon 
{
    Entity::Entity(const int id)
        : m_id(id)
    {
        //
    }

    Entity::Entity(const int id, const std::initializer_list<Component*> components)
        : m_id(id)
    {
        for (auto& component : components) {
            m_components.emplace_back(component);
        }
    }

    Entity::~Entity()
    {
        for (auto* c : m_components)
        {
            delete c;
        }
    }

    template <typename T>
    void Entity::AddComponent(Component* component)
    {
        m_components.emplace_back(component);
    }
        
    int Entity::GetId() const 
    {
        return m_id; 
    }
}