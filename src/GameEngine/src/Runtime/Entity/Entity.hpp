/**
 * {SourceHeader}
 */

#pragma once

#include <stdexcept>
#include <typeindex>

#include <Runtime/Entity/Entity.hpp>
#include <Runtime/Runtime/Input.hpp>
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
                auto type = std::type_index(typeid(T));
                auto it = m_components.find(type);

                if (it != m_components.end())
                {
                    return dynamic_cast<T*>(it->second);
                }

                throw std::runtime_error("Component of requested type not found!");
            }

            // Check if the entity has a component of type T
            // we can do some optimizing in the storage.
            template<typename T>
            bool HasComponent() const
            {
                auto type = std::type_index(typeid(T));
                return m_components.find(type) != m_components.end();
            }

            [[nodiscard]] EntityID GetId() const;

        public:
            virtual void OnInit();
            virtual void OnUpdate();
            virtual void OnRender();
            virtual void OnDestroy() {};
            void HandleInput(OpenGLInput* input);

        private:
            EntityID m_id;
            std::unordered_map<std::type_index, Component*> m_components;
    };
}