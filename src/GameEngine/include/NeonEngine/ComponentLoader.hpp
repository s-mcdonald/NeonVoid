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

#include <NeonEngine/Types.hpp>
#include <NeonEngine/Components.hpp>
#include <NeonEngine/RuntimeBridge.hpp>

namespace Neon
{
    class ComponentLoader
    {
        public:
            static Component* MakeComponentReal(YComponent component, Application& app);

            static std::unordered_map<std::string, Component*> CollectComponents(const std::vector<YComponent>& components, Application& app);
    };
}
