/**
 * 
 */
#pragma once

#include <vector>

#include <Runtime/Runtime.hpp>
#include <Runtime/Input/Input.hpp>

namespace Neon 
{
    class Component;

    class Entity 
    {
        public:
            Entity() = delete;
            explicit Entity(const EntityID id) : m_id(id) {};
            explicit Entity(EntityID id, std::initializer_list<Component*> components);
            virtual ~Entity();
        
            void AddComponent(Component* component);
        
            [[nodiscard]] EntityID GetId() const;

        public:
            virtual void OnInit();
            virtual void OnUpdate();
            virtual void OnDestroy() {};
            void HandleInput(Input* input);

        private:
            EntityID m_id;
            std::vector<Component*> m_components;
    };
}