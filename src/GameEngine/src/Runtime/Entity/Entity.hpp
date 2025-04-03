/**
 * 
 */
#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <unordered_map>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    class Component;

    class Entity 
    {
        public:
            explicit Entity(int id);
            explicit Entity(uint32_t id, std::initializer_list<Component*> components);
            virtual ~Entity();
        
            template <typename T>
            void AddComponent(Component* component);
        
            [[nodiscard]] uint32_t GetId() const;

        public:
            virtual void OnInit() {};
            virtual void OnUpdate() {};
            virtual void OnDestroy() {};

        private:
            uint32_t m_id;
            std::vector<Component*> m_components;

    };
}