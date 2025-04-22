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

        for (auto& comp : components)
        {
            if (comp.type == "audio")
            {
                auto* theComponent = new AudioComponent(comp.audioConfig->path);
                Volume v(comp.audioConfig->volume);
                theComponent->SetVolume(v);
                if (comp.audioConfig->loop)
                {
                    theComponent->TriggerPlayRepeat();
                }
                else
                {
                    theComponent->TriggerPlayOnce();
                }

                componentsForScene.emplace(comp.type, theComponent);
            }

            if (comp.type == "position")
            {
                auto* theComponent = new PositionComponent(comp.posConfig->p);
                componentsForScene.emplace(comp.type, theComponent);
            }

            if (comp.type == "movement")
            {
                // @todo, add data: key bindings
                auto* theComponent = new MovementComponent();
                componentsForScene.emplace(comp.type, theComponent);
            }

            if (comp.type == "shader")
            {
                auto vertexPath = comp.shaderConfig->dir + comp.shaderConfig->vertexShader;
                auto fragPath = comp.shaderConfig->dir + comp.shaderConfig->fragShader;

                auto shaderPgm = bridge.CreateShader(vertexPath,fragPath);

                // @todo, make PosComp accept point so we can pass initial
                auto* theComponent = new ShaderComponent(comp.shaderConfig->vertices, shaderPgm);

                componentsForScene.emplace(comp.type, theComponent);
            }

            if (comp.type == "text")
            {
                // built-in shader for text
                auto vertexPath = "./assets/shaders/Text/shader.vert";
                auto fragPath = "./assets/shaders/Text/shader.frag";

                auto shaderPgm = bridge.CreateShader(vertexPath,fragPath);
                auto* theComponent = new TextComponent(comp.textConfig.text, shaderPgm);
                componentsForScene.emplace(comp.type, theComponent);
            }

            if (comp.type == "script")
            {
                // @todo: reminder to clean this up later
                ScriptType scriptType = FunctionRegistry::Get().FetchScriptType(comp.textConfig.text);
                switch(scriptType)
                {
                    case ScriptType::SceneInit:
                    {
                        auto funcCallback = FunctionRegistry::Get().FetchSceneInitScript(comp.textConfig.text);
                        auto* theComponent = new ScriptComponent(funcCallback, ScriptType::SceneInit);
                        componentsForScene.emplace(comp.type, theComponent);
                        break;
                    }

                    case ScriptType::SceneUpdate:
                    {
                        auto funcCallback = FunctionRegistry::Get().FetchSceneUpdateScript(comp.textConfig.text);
                        auto* theComponent = new ScriptComponent(funcCallback, ScriptType::SceneUpdate);
                        componentsForScene.emplace(comp.type, theComponent);
                        break;
                    }

                    case ScriptType::EntityUpdate:
                    {
                        auto funcCallback = FunctionRegistry::Get().FetchEntityUpdateScript(comp.textConfig.text);
                        auto* theComponent = new ScriptComponent(funcCallback, ScriptType::EntityUpdate);
                        componentsForScene.emplace(comp.type, theComponent);
                        break;
                    }

                    default:
                    {
                        // @todo: lets notify the game developer that scene or entity script not found
                        break;
                    }
                }
            }

            if (comp.type == "collision")
            {
                auto* theComponent = new CollisionComponent(comp.posConfig->p.x, comp.posConfig->p.y);
                componentsForScene.emplace(comp.type, theComponent);
            }
        }

        return componentsForScene;
    }
}