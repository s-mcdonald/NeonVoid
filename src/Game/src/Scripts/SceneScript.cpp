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

std::function<void(Neon::Scene* scene)> SceneScript::GetLevelOneInitScript()
{
    return[](Neon::Scene* scene)
    {
        if (scene->MakeComponent("sceneCompTimer"))
        {
            auto timer = static_cast<Neon::TimerComponent*>(scene->GetComponent("sceneCompTimer"));

            timer->Start();

            std::cout << "Render sceneCompTimer" << std::endl;
        }

        if (scene->MakeComponent("sceneCompBackgroundSound"))
        {
            std::cout << "Render sceneCompBackgroundSound" << std::endl;
        }

        if (scene->MakeComponent("sceneCompText"))
        {
            std::cout << "Render sceneCompText" << std::endl;
        }

        if (scene->MakeComponent("sceneCompShader"))
        {
            std::cout << "Render sceneCompShader" << std::endl;
        }

        if (scene->MakeEntity("mainPlayer"))
        {
            std::cout << "Created Player Entity" << std::endl;
        }

        if (scene->MakeEntity("cherryHealthPack"))
        {
            std::cout << "Created Cherry" << std::endl;
        }

        if (scene->MakeEntity("bombEnemy"))
        {
            std::cout << "Bomb Cherry" << std::endl;
        }
    };
}

std::function<void(Neon::Scene* scene)> SceneScript::GetLevelOneUpdateScript()
{
    return[](Neon::Scene* scene)
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

std::function<void(Neon::Scene* scene)> SceneScript::GetSceneTimerScript()
{
    return[](Neon::Scene* scene)
    {
        std::cout << "Scene Timer real callback here..." << std::endl;
    };
}
