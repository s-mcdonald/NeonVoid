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
#include <NeonEngine/All.hpp>

class SceneScript
{
    public:
        static std::function<void(Neon::Scene* scene)> GetLevelOneInitScript();
        static std::function<void(Neon::Scene* scene)> GetLevelOneUpdateScript();
};

class EntityScript
{
    public:
        static std::function<void(Neon::Entity* e, Neon::Scene* scene)> GetPlayerUpdateScript();
        static std::function<void(Neon::Entity* e, Neon::Scene* scene)> GetBombUpdateScript();
        static std::function<void(Neon::Entity* e, Neon::Scene* scene)> GetCherryUpdateScript();
};


