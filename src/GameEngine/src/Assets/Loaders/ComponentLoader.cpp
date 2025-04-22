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

#include <filesystem>
#include <iostream>
#include <unordered_map>

#include <NeonEngine/Types.hpp>
#include <NeonEngine/ComponentLoader.hpp>
#include <NeonEngine/Components.hpp>
#include <NeonEngine/FunctionRegistry.hpp>
#include <NeonEngine/RuntimeBridge.hpp>

namespace Neon
{
    Component* ComponentLoader::MakeComponentReal(YComponent yComp, RuntimeBridge& bridge)
    {
        if (yComp.type == "audio")
        {
            auto* theComponent = new AudioComponent(yComp.audioConfig->path);
            Volume v(yComp.audioConfig->volume);
            theComponent->SetVolume(v);
            if (yComp.audioConfig->loop)
            {
                theComponent->TriggerPlayRepeat();
            }
            else
            {
                theComponent->TriggerPlayOnce();
            }

            theComponent->OnInit();

            return theComponent;
        }

        if (yComp.type == "position")
        {
            auto* theComponent = new PositionComponent(yComp.posConfig->p);
            theComponent->OnInit();
            return theComponent;
        }

        if (yComp.type == "movement")
        {
            // @todo, add data: key bindings
            auto* theComponent = new MovementComponent();
            theComponent->OnInit();
            return theComponent;
        }

        if (yComp.type == "shader")
        {
            auto vertexPath = yComp.shaderConfig->dir + yComp.shaderConfig->vertexShader;
            auto fragPath = yComp.shaderConfig->dir + yComp.shaderConfig->fragShader;

            auto shaderPgm = bridge.CreateShader(vertexPath,fragPath);

            // @todo, make PosComp accept point so we can pass initial
            auto* theComponent = new ShaderComponent(yComp.shaderConfig->vertices, shaderPgm);
            theComponent->OnInit();
            return theComponent;
        }

        if (yComp.type == "text")
        {
            // built-in shader for text
            auto vertexPath = "./assets/shaders/Text/shader.vert";
            auto fragPath = "./assets/shaders/Text/shader.frag";

            auto shaderPgm = bridge.CreateShader(vertexPath,fragPath);
            auto* theComponent = new TextComponent(yComp.textConfig.text, shaderPgm);
            theComponent->OnInit();
            return theComponent;
        }

        if (yComp.type == "collision")
        {
            auto* theComponent = new CollisionComponent(yComp.posConfig->p.x, yComp.posConfig->p.y);
            theComponent->OnInit();
            return theComponent;
        }

        if (yComp.type == "script")
        {
            // @todo: reminder to clean this up later
            ScriptType scriptType = FunctionRegistry::Get().FetchScriptType(yComp.textConfig.text);
            switch(scriptType)
            {
                case ScriptType::SceneInit:
                {
                    auto funcCallback = FunctionRegistry::Get().FetchSceneInitScript(yComp.textConfig.text);
                    auto* theComponent = new ScriptComponent(funcCallback, ScriptType::SceneInit);
                    return theComponent;
                    break;
                }

                case ScriptType::SceneUpdate:
                {
                    auto funcCallback = FunctionRegistry::Get().FetchSceneUpdateScript(yComp.textConfig.text);
                    auto* theComponent = new ScriptComponent(funcCallback, ScriptType::SceneUpdate);
                    return theComponent;
                    break;
                }

                case ScriptType::EntityUpdate:
                {
                    auto funcCallback = FunctionRegistry::Get().FetchEntityUpdateScript(yComp.textConfig.text);
                    auto* theComponent = new ScriptComponent(funcCallback, ScriptType::EntityUpdate);
                    return theComponent;
                    break;
                }

                default:
                {
                    // @todo: lets notify the game developer that scene or entity script not found
                    break;
                }
            }
        }
    }

    /**
     * This should only be called when creating/Making entities or components since this will call
     * new on them.
     */
    std::unordered_map<std::string, Component*> ComponentLoader::CollectComponents(
        std::vector<YComponent> components,
        RuntimeBridge& bridge
        )
    {
        std::unordered_map<std::string, Component*> componentsForScene;

        for (auto& yComp : components)
        {
            componentsForScene.emplace(yComp.type, MakeComponentReal(yComp, bridge));
        }

        return componentsForScene;
    }
}