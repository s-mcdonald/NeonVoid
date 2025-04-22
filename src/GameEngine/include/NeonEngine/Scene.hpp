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

#include <NeonEngine/Components.hpp>
#include <NeonEngine/Entity.hpp>

#include <NeonEngine/CollisionSystem.hpp>

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


            bool IsInitialized() const;
            void HandleInput(Input* input);
            virtual void OnInit() {};
            virtual void OnUpdate() {};
            virtual void OnRender() {};
            virtual void OnDestroy() {};

            void AddEntity(EntityID id, Entity* entity);
            void AddComponent(const std::string& tag, Component* component);
            Component* GetComponent(const std::string& tag);
            Entity* GetEntity(EntityID id) const;
            Entity* GetPlayerEntity() const;

            SceneType GetSceneType() const;

        protected:
            Entity* MakeEntity(const YEntity& yentity);
            void MakeAll();

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
    };
}
