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

#include <string>
#include <unordered_map>

#include <NeonEngine/Types.hpp>
#include <NeonEngine/Components.hpp>
#include <NeonEngine/Entity.hpp>
#include <NeonEngine/Application.hpp>
#include <NeonEngine/CollisionSystem.hpp>
#include <NeonEngine/PhysixSystem.hpp>

namespace Neon
{
    class Scene
    {
        public:
            Scene() = delete;
            explicit Scene(Application* app, const YScene config);
            virtual ~Scene();


            void Init();
            void Update();
            void Render();
            void Destroy();
            void ProcessPendingDeletions();

            bool IsInitialized() const;
            void HandleInput(Input* input);

            void AddEntity(EntityID id, Entity* entity);
            void AddComponent(const std::string& tag, Component* component);

            template<typename T>
            T* GetComponentByTag(const std::string& tag)
            {
                if (m_components.find(tag) != m_components.end())
                {
                    return static_cast<T*>(m_components[tag]);
                }

                return nullptr;
            }

            // deprecated
            Component* GetComponent(const std::string& tag);
            void DestroyEntity(const EntityID id);
            void DestroyEntity(const Entity* entity);
            Entity* GetEntity(EntityID id) const;
            Entity* GetPlayerEntity() const;

            SceneType GetSceneType() const;

            bool MakeComponent(const std::string& compoTag);
            Entity* MakeEntity(const std::string& entityTag);

            uint32_t EntityCount() const
            {
                return m_entities.size();
            }

            uint32_t ComponentCount() const
            {
                return m_components.size();
            }

        private:
            template <typename T>
            void InitRenderable(const T& t);

            template <typename T>
            void UpdateRenderable(const T& t);

            template <typename T>
            void RenderRenderable(const T& t);

            template <typename T>
            void DestroyRenderable(const T& t);

            template <typename T>
            void HandlesInput(const T& t, Input* input);

        protected:
            std::unordered_map<EntityID, Entity*> m_entities;

        private:
            Application* mx_app{nullptr};
            YScene m_sceneConfig;
            bool m_isInitialized = false;
            std::unordered_map<std::string, Component*> m_components;
            uint32_t m_nextEntityID;
            CollisionSystem m_collisionSystem;
            PhysixSystem m_physixSystem;
            std::vector<EntityID> m_pendingDeletions;
    };
}
