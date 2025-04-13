/**
 * 
 */
#pragma once

#include <vector>
#include <stdexcept>

#include <Runtime/Engine/Input.hpp>
#include <Runtime/Entity/Entity.hpp>
#include <Runtime/Types.hpp>

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

            template<typename T>
            T* GetComponent()
            {
                for (auto* component : m_components)
                {
                    if (auto* target = dynamic_cast<T*>(component))
                    {
                        return target;
                    }
                }

                throw std::runtime_error("Component of requested type not found!");
            }

            // Check if the entity has a component of type T
            // we can do some optimizing in the storage.
            template<typename T>
            bool HasComponent() const
            {
                for (auto* component : m_components)
                {
                    if (dynamic_cast<T*>(component))
                    {
                        return true;
                    }
                }
                return false;
            }

            [[nodiscard]] EntityID GetId() const;

        public:
            virtual void OnInit();
            virtual void OnUpdate();
            virtual void OnDestroy() {};
            void HandleInput(OpenGLInput* input);

        private:
            EntityID m_id;

            // optimize the storage.
            std::vector<Component*> m_components;
    };
}