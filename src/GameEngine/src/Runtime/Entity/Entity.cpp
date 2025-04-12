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

        for (auto& component : components)
        {
            m_components.emplace_back(component);
        }
    }

    Entity::~Entity()
    {
        for (const auto& c : m_components)
        {
            delete c;
        }
    }

    void Entity::OnInit()
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
                std::cout << "Entity::Init" << std::endl;
        #endif

        for (const auto& component : m_components)
        {
            component->OnInit();
        }
    }

    void Entity::OnUpdate()
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "Entity::Update" << std::endl;
        #endif

        for (const auto& component : m_components)
        {
            component->OnUpdate();
        }
    }

    void Entity::AddComponent(Component* component)
    {
        m_components.emplace_back(component);
    }

    EntityID Entity::GetId() const
    {
        return m_id; 
    }
}