/**
 * {SourceHeader}
 */

#include <Runtime/Runtime.hpp>
#include <Runtime/Entity/Entity.hpp>

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
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "Entity::Init" << std::endl;
        #endif

        for (const auto& [_, component] : m_components)
        {
            component->OnInit();
        }
    }

    void Entity::OnUpdate()
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "Entity::Update" << std::endl;
        #endif

        for (const auto& [_, component] : m_components)
        {
            component->OnUpdate();
        }
    }

    void Entity::OnRender()
    {
#if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
        std::cout << "Entity::Render" << std::endl;
#endif

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

    void Entity::HandleInput(OpenGLInput* input)
    {
        try
        {
            auto* movementComponent = GetComponent<MovementComponent>();
            movementComponent->HandleInput(input);
        }
        catch (const std::runtime_error& ex)
        {
            // ..
        }
    }

    EntityID Entity::GetId() const
    {
        return m_id; 
    }
}