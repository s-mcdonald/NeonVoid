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
            Entity(int id);
            ~Entity();
        
            template <typename T>
            void AddComponent(Component* component);
        
            template <typename T>
            T* GetComponent();
        
            int GetId() const;

        private:
            int m_id;
            std::unordered_map<std::string, Component*> components;
    };
}