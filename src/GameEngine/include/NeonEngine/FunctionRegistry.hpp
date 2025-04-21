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

#include <unordered_map>
#include <functional>
#include <string>

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
            void Register(const std::string& name, Func&& func)
            {
                m_functions[name] = std::forward<Func>(func);
            }

            std::function<void(Scene* scene)> Fetch(const std::string& name)
            {
                auto it = m_functions.find(name);
                if (it != m_functions.end())
                {
                    return it->second;
                }
                return nullptr;
            }

        private:
            std::unordered_map<std::string, std::function<void(Scene* scene)>> m_functions;
    };
}

