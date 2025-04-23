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
    std::function<void(Scene* scene)> SceneScript::GetLevelOneInitScript()
    {
        return[](Scene* scene)
        {
            if (scene->MakeComponent("scene_renderable_test"))
            {
                std::cout << "Render components" << std::endl;
            }
            //

            if (scene->MakeEntity("mainPlayer"))
            {
                std::cout << "Created Player Entity" << std::endl;
            }

            if (scene->MakeEntity("cherryHealthPack"))
            {
                std::cout << "Created Cherry" << std::endl;
            }
        };
    }

    std::function<void(Scene* scene)> SceneScript::GetLevelOneUpdateScript()
    {
        return[](Scene* scene)
        {
            if (scene->GetPlayerEntity())
            {
                std::cout << "We found the main player" << std::endl;
            }
            else
            {
                std::cout <<"We dont have a player entity" << std::endl;
            }
        };
    }
}

