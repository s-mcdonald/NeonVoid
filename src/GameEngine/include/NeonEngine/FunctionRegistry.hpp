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
            void RegisterSceneScript(const std::string& name, Func&& func)
            {
                m_functionsScenes[name] = std::forward<Func>(func);
            }

            template<typename Func>
            void RegisterEntityScript(const std::string& name, Func&& func)
            {
                m_functionsEntity[name] = std::forward<Func>(func);
            }

            ScriptType FetchScriptType(const std::string& name)
            {
                auto it = m_functionsScenes.find(name);
                if (it != m_functionsScenes.end())
                {
                    return ScriptType::Scene;
                }

                auto eit = m_functionsEntity.find(name);
                if (eit != m_functionsEntity.end())
                {
                    return ScriptType::Entity;
                }

                return ScriptType::None;
            }

            std::function<void(Scene* scene)> FetchSceneScript(const std::string& name)
            {
                auto it = m_functionsScenes.find(name);
                if (it != m_functionsScenes.end())
                {
                    return it->second;
                }
                return nullptr;
            }

            std::function<void(Entity* entity, Scene* scene)> FetchEntityScript(const std::string& name)
            {
                auto it = m_functionsEntity.find(name);
                if (it != m_functionsEntity.end())
                {
                    return it->second;
                }
                return nullptr;
            }

        private:
            std::unordered_map<std::string, std::function<void(Scene* scene)>> m_functionsScenes;
            std::unordered_map<std::string, std::function<void(Entity* entity, Scene* scene)>> m_functionsEntity;
    };
}

