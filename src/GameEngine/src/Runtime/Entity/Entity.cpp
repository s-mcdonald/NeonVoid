/**
 * 
 */
#include "Runtime/Runtime.hpp"

#include "Entity.hpp"

namespace Neon 
{
    Entity::Entity(int id) 
        : m_id(id)
    {
        //
    }

    Entity::~Entity()
    {
        for (auto& pair : components) 
        {
            delete pair.second;
        }
    }

    template <typename T>
    void Entity::AddComponent(Component* component)
    {
        components[typeid(T).name()] = component;
    }

    template <typename T>
    T* Entity::GetComponent() 
    {
        auto it = components.find(typeid(T).name());
        if (it != components.end()) 
        {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }
        
    int Entity::GetId() const 
    {
        return m_id; 
    }
}