/**
 * 
 */
#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <unordered_map>

#include "Runtime/Runtime.hpp"
#include "Runtime/Entity/Entity.hpp"

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
            void Destroy();
            virtual void OnInit() {};
            virtual void OnUpdate() {};
            virtual void OnDestroy() {};
            bool IsInitialized() const;

        public:
            void AddComponent(const std::string& tag, Component* component);
            Component* GetComponent(const std::string& tag);

            // void SetBackgroundAudio(AudioComponent component);
            // void SetBackgroundShader BackgroundImage ?
            // void SetMaxTimeAllowedInScene

            SceneType GetSceneType() const;

        private:
            template <typename T>
            void InitRenderable(const T& t);

            template <typename T>
            void UpdateRenderable(const T& t);

            template <typename T>
            void DestroyRenderable(const T& t);

        protected:
            std::unordered_map<std::string, Entity*> m_entities;

        private:
            SceneType m_scene_type;
            bool m_isInitialized = false;
            std::unordered_map<std::string, Component*> m_components;
    };
}