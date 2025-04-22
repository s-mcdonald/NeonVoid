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

#include "Types.hpp"

namespace Neon
{
    class FunctionRegistry
    {
        public:
            static FunctionRegistry& Get()
            {
                static FunctionRegistry instance;
                return instance;
            }

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

            ScriptType FetchScriptType(const std::string& name)
            {
                auto it = m_functionsUpdateScenes.find(name);
                if (it != m_functionsUpdateScenes.end())
                {
                    return ScriptType::SceneUpdate;
                }

                auto eit = m_functionsEntity.find(name);
                if (eit != m_functionsEntity.end())
                {
                    return ScriptType::EntityUpdate;
                }

                auto eiti = m_functionsInitScenes.find(name);
                if (eiti != m_functionsInitScenes.end())
                {
                    return ScriptType::SceneInit;
                }

                return ScriptType::None;
            }

            std::function<void(Scene* scene)> FetchSceneInitScript(const std::string& name)
            {
                auto it = m_functionsInitScenes.find(name);
                if (it != m_functionsInitScenes.end())
                {
                    return it->second;
                }
                return nullptr;
            }

            std::function<void(Scene* scene)> FetchSceneUpdateScript(const std::string& name)
            {
                auto it = m_functionsUpdateScenes.find(name);
                if (it != m_functionsUpdateScenes.end())
                {
                    return it->second;
                }
                return nullptr;
            }

            std::function<void(Entity* entity, Scene* scene)> FetchEntityUpdateScript(const std::string& name)
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

