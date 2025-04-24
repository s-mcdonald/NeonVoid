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
#include <cstdlib>
#include <ctime>


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
        // ...
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
        if ( p.y < -1.2f)
        {
            // if (scene != nullptr)
            // scene->DestroyEntity(e);
        }
        else
        {
            p.y -= e->GetUserFlag(BOMB_FLAG_SPEED_FAST) == false ? SPEED_BOMB_SLOW : SPEED_BOMB_FAST;

            x->SetPoint(p);
        }
    };
}

//
// Cherry Entity OnUpdate
//
std::function<void(Entity* e, Scene* scene)> EntityScript::GetCherryUpdateScript()
{
    return[](Entity* e, Scene* scene)
    {
        if (e == nullptr)
        {
            return;
        }

        auto* x = e->GetComponent<PositionComponent>();
        if (!x)
        {
            return;
        }

        Point p = x->GetPoint();

        if ( p.y > 1.2)
        {
            // if (scene != nullptr && e != nullptr)
                // scene->DestroyEntity(e);
        }
        else
        {
            p.y += e->GetUserFlag(BOMB_FLAG_SPEED_FAST) == false ? SPEED_CHERRY_SLOW : SPEED_CHERRY_FAST;
            x->SetPoint(p);
        }
    };
}
