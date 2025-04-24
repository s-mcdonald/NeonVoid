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

#pragma once

#include <stdexcept>
#include <typeindex>
#include <unordered_map>

#include <NeonEngine/Types.hpp>
#include <NeonEngine/Components.hpp>

namespace Neon 
{
    class Entity 
    {
        public:
            Entity() = delete;
            explicit Entity(
                const EntityID id, const std::string& tag, const EntityType type, Scene* scene)
                : m_id(id)
                , m_tag(tag)
                , m_type(type)
                , mx_scene(scene) {};

            virtual ~Entity();

            std::string GetTag() const
            {
                return m_tag;
            }

            EntityType GetType() const
            {
                return m_type;
            }
        
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

                return nullptr;
            }

            // Check if the entity has a component of type T
            // we can do some optimizing in the storage.
            template<typename T>
            bool HasComponent() const
            {
                auto type = std::type_index(typeid(T));
                return m_components.contains(type);
            }

            [[nodiscard]] EntityID GetId() const;

            virtual void OnInit();
            virtual void OnUpdate();
            virtual void OnRender();
            virtual void OnDestroy() {};
            void HandleInput(Input* input);

        private:
            EntityID m_id;
            std::string m_tag;
            EntityType m_type;
            Scene* mx_scene;
            std::unordered_map<std::type_index, Component*> m_components;
    };
}