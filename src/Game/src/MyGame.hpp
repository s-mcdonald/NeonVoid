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

#include <NeonEngine/All.hpp>

#include <GameScripts.hpp>

using namespace Neon;

class MyGame final : public Application
{
    public:
        MyGame()
        {
            // we could also make the FR as part of Application!!!!\
            // we can do that later
            GetScriptRegistry().RegisterScript("Scene::OnInit", ScriptType::SceneInit, SceneScript::GetLevelOneInitScript());
            GetScriptRegistry().RegisterScript("Scene::OnUpdate", ScriptType::SceneUpdate,  SceneScript::GetLevelOneUpdateScript());
            GetScriptRegistry().RegisterScript("Scene::Timer", ScriptType::SceneUpdate,  SceneScript::GetSceneTimerScript());
            GetScriptRegistry().RegisterScript("Entity::Cherry::OnUpdate",  ScriptType::EntityUpdate, EntityScript::GetCherryUpdateScript());

            // @todo: Use a filesystem lib to parse filenames
            SetSceneYaml("./assets/game.yaml");
        }

        [[nodiscard]] bool Initialize()
        {
            // return Application::Initialize(800, 600, "Neon Void (0.0.6)");
            return Application::Initialize(1920, 1080, "Neon Void (0.0.6)");
        }
};
