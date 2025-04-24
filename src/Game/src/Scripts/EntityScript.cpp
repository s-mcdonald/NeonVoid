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

#include <functional>
#include <iostream>

#include <NeonEngine/All.hpp>
#include <GameScripts.hpp>

using namespace Neon;

//
// Player Entity OnUpdate
//
std::function<void(Entity* entity, Scene* scene)> EntityScript::GetPlayerUpdateScript()
{
    return[](Entity* entity, Scene* scene)
    {
        if (auto* comp = entity->GetComponentByTag<AudioComponent>("bombAudio"))
        {

        }
    };
}

//
// BOMB Entity OnUpdate
//
std::function<void(Entity* e, Scene* scene)> EntityScript::GetBombUpdateScript()
{
    return[](Entity* e, Scene* scene)
    {
        auto* x = e->GetComponent<PositionComponent>();
        if (!x)
        {
            return;
        }

        Point p = x->GetPoint();
        p.y -= SPEED_BOMB_SLOW;
        x->SetPoint(p);
    };
}

//
// Cherry Entity OnUpdate
//
std::function<void(Entity* e, Scene* scene)> EntityScript::GetCherryUpdateScript()
{
    return[](Entity* e, Scene* scene)
    {
        auto* x = e->GetComponent<PositionComponent>();
        if (!x)
        {
            return;
        }

        Point p = x->GetPoint();
        p.y += SPEED_CHERRY_SLOW;
        x->SetPoint(p);
    };
}
