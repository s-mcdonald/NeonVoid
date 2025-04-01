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
            virtual ~Entity();
        
            template <typename T>
            void AddComponent(Component* component);
        
            template <typename T>
            T* GetComponent();
        
            int GetId() const;

        public:
            virtual void OnInit() {};
            virtual void OnUpdate() {};
            virtual void OnDestroy() {};

        private:
            int m_id;
            std::unordered_map<std::string, Component*> components;
    };
}