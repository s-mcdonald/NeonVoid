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
            void RegisterScript(const std::string& name, ScriptType type, Func&& func)
            {
                m_scripts[name] = ScriptEntry{ type, std::forward<Func>(func) };
            }

            ScriptType GetScriptType(const std::string& name) const
            {
                auto it = m_scripts.find(name);
                if (it != m_scripts.end())
                {
                    return it->second.type;
                }
                return ScriptType::None;
            }

            std::function<void(Scene* scene)> FetchSceneScript(const std::string& name) const
            {
                auto it = m_scripts.find(name);
                if (it != m_scripts.end() && it->second.type != ScriptType::EntityUpdate)
                {
                    return std::get<std::function<void(Scene*)>>(it->second.function);
                }
                return nullptr;
            }

            std::function<void(Entity* entity, Scene* scene)> FetchEntityScript(const std::string& name) const
            {
                auto it = m_scripts.find(name);
                if (it != m_scripts.end() && it->second.type == ScriptType::EntityUpdate)
                {
                    return std::get<std::function<void(Entity*, Scene*)>>(it->second.function);
                }
                return nullptr;
            }

        private:
            struct ScriptEntry
            {
                ScriptType type;
                std::variant<std::function<void(Scene*)>, std::function<void(Entity*, Scene*)>> function;
            };

            std::unordered_map<std::string, ScriptEntry> m_scripts;
    };
}

