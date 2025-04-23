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

#include <functional>
#include <string>
#include <unordered_map>

#include <NeonEngine/Types.hpp>

namespace Neon
{
    class ScriptRegistry
    {
        public:
            ScriptRegistry() = default;

            template<typename Func>
            void RegisterSceneInitScript(const std::string& name, Func&& func)
            {
                m_functionsInitScenes[name] = std::forward<Func>(func);
            }

            template<typename Func>
            void RegisterSceneUpdateScript(const std::string& name, Func&& func)
            {
                m_functionsUpdateScenes[name] = std::forward<Func>(func);
            }

            template<typename Func>
            void RegisterEntityUpdateScript(const std::string& name, Func&& func)
            {
                m_functionsEntity[name] = std::forward<Func>(func);
            }

            ScriptType GetScriptType(const std::string& name) const
            {
                if (m_functionsUpdateScenes.count(name)) return ScriptType::SceneUpdate;
                if (m_functionsEntity.count(name)) return ScriptType::EntityUpdate;
                if (m_functionsInitScenes.count(name)) return ScriptType::SceneInit;
                return ScriptType::None;
            }

            std::function<void(Scene* scene)> FetchSceneInitScript(const std::string& name) const
            {
                auto it = m_functionsInitScenes.find(name);
                if (it != m_functionsInitScenes.end())
                {
                    return it->second;
                }
                return nullptr;
            }

            std::function<void(Scene* scene)> FetchSceneUpdateScript(const std::string& name) const
            {
                auto it = m_functionsUpdateScenes.find(name);
                if (it != m_functionsUpdateScenes.end())
                {
                    return it->second;
                }
                return nullptr;
            }

            std::function<void(Entity* entity, Scene* scene)> FetchEntityUpdateScript(const std::string& name) const
            {
                auto it = m_functionsEntity.find(name);
                if (it != m_functionsEntity.end())
                {
                    return it->second;
                }
                return nullptr;
            }

        private:
            std::unordered_map<std::string, std::function<void(Scene* scene)>> m_functionsInitScenes;
            std::unordered_map<std::string, std::function<void(Scene* scene)>> m_functionsUpdateScenes;
            std::unordered_map<std::string, std::function<void(Entity* entity, Scene* scene)>> m_functionsEntity;
    };
}

