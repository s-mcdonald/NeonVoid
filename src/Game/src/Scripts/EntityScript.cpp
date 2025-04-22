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

namespace Neon
{
    // Player Entity
    std::function<void(Entity* e, Scene* scene)> EntityScript::GetPlayerUpdateScript()
    {
        return[](Entity* e, Scene* scene)
        {
            auto c = e->GetComponent<CollisionComponent>();
            if (c)
            {
                //..
            }
        };
    }

    // BOMB Entity !!!!
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
            p.y -= 0.0003;
            x->UpdateData(p);
        };
    }

    // Cherry Entity
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
            p.y += 0.0001;
            x->UpdateData(p);
        };
    }
}

