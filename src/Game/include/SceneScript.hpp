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

namespace Neon
{
    class SceneScript
    {
        public:
            static std::function<void(Scene* scene)> GetUpdateScript()
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
    };
}

