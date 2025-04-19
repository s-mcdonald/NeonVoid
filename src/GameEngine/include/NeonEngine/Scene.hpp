/**
 * {SourceHeader}
 */

#pragma once

#include <string>
#include <unordered_map>

#include <NeonEngine/Entity.hpp>
#include <NeonEngine/Components.hpp>

namespace Neon
{
    class Scene
    {
        public:
            Scene() = delete;
            explicit Scene(SceneType type);
            virtual ~Scene();

        public:
            void Init();
            void Update();
            void Render();
            void Destroy();

            void HandleInput(Input* input);
            virtual void OnInit() {};
            virtual void OnUpdate() {};
            virtual void OnRender() {};
            virtual void OnDestroy() {};

            bool IsInitialized() const;

        public:
            void AddEntity(EntityID id, Entity* entity);
            void AddComponent(const std::string& tag, Component* component);
            Component* GetComponent(const std::string& tag);

        public:
            SceneType GetSceneType() const;

        protected:
            Entity* MakeEntity(const YEntity& yentity);

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
            SceneType m_sceneType;
            bool m_isInitialized = false;
            std::unordered_map<std::string, Component*> m_components;
            uint32_t m_nextEntityID;
    };
}
