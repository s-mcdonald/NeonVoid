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

constexpr float SPEED_CHERRY_SLOW   = 0.001;
constexpr float SPEED_CHERRY_FAST   = 0.005;

constexpr float SPEED_BOMB_SLOW     = 0.001;
constexpr float SPEED_BOMB_MEDIUM   = 0.003;
constexpr float SPEED_BOMB_FAST     = 0.005;

constexpr float INTERVAL_TOLERANCE  = 0.01f;
constexpr float CHERRY_SPAWN_INTERVAL = 5.0f;

class SceneScript
{
    public:
        static std::function<void(Neon::Scene* scene)> GetLevelOneInitScript();
        static std::function<void(Neon::Scene* scene)> GetLevelOneUpdateScript();
        static std::function<void(Neon::Scene* scene)> GetSceneTimerScript();
};

class EntityScript
{
    public:
        static std::function<void(Neon::Entity* e, Neon::Scene* scene)> GetPlayerUpdateScript();
        static std::function<void(Neon::Entity* e, Neon::Scene* scene)> GetBombUpdateScript();
        static std::function<void(Neon::Entity* e, Neon::Scene* scene)> GetCherryUpdateScript();
};


