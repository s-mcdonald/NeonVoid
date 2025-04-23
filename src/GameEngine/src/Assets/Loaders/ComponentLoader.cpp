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
#include <NeonEngine/RuntimeBridge.hpp>
#include <NeonEngine/ScriptRegistry.hpp>
#include <NeonEngine/Application.hpp>

///
/// @todo: future task: convert this into a proper Factory class, i.e CreateAudioComponent, CreateTimeComponent
///
namespace Neon
{
    Component* ComponentLoader::MakeComponentReal(const YComponent& component, Application& app)
    {
        if (component.type == "audio")
        {
            auto* theComponent = new AudioComponent(component.audioConfig->path);
            Volume v(component.audioConfig->volume);
            theComponent->SetVolume(v);
            if (component.audioConfig->loop)
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

        if (component.type == "position")
        {
            auto* theComponent = new PositionComponent(component.posConfig->p);
            theComponent->OnInit();
            return theComponent;
        }

        if (component.type == "movement")
        {
            // @todo, add data: key bindings
            auto* theComponent = new MovementComponent();
            theComponent->OnInit();
            return theComponent;
        }

        if (component.type == "shader")
        {
            auto vertexPath = component.shaderConfig->dir + component.shaderConfig->vertexShader;
            auto fragPath = component.shaderConfig->dir + component.shaderConfig->fragShader;

            auto shaderPgm = app.GetBridge().CreateShader(vertexPath,fragPath);

            // @todo, make PosComp accept point so we can pass initial
            auto* theComponent = new ShaderComponent(component.shaderConfig->vertices, shaderPgm);
            theComponent->OnInit();
            return theComponent;
        }

        if (component.type == "text")
        {
            // built-in shader for text
            auto vertexPath = "./assets/shaders/Text/shader.vert";
            auto fragPath = "./assets/shaders/Text/shader.frag";

            auto shaderPgm = app.GetBridge().CreateShader(vertexPath,fragPath);
            auto* theComponent = new TextComponent(component.textConfig.text, shaderPgm);
            theComponent->OnInit();
            return theComponent;
        }

        if (component.type == "collision")
        {
            auto* theComponent = new CollisionComponent(component.posConfig->p.x, component.posConfig->p.y);
            theComponent->OnInit();
            return theComponent;
        }

        if (component.type == "script")
        {
            // @todo: reminder to clean this up later
            switch (ScriptType scriptType = app.GetScriptRegistry().GetScriptType(component.textConfig.text))
            {
                case ScriptType::SceneInit:
                    {
                        auto funcCallback = app.GetScriptRegistry().FetchSceneInitScript(component.textConfig.text);
                        auto* theComponent = new ScriptComponent(funcCallback, ScriptType::SceneInit);
                        return theComponent;
                        break;
                    }

                case ScriptType::SceneUpdate:
                    {
                        auto funcCallback = app.GetScriptRegistry().FetchSceneUpdateScript(component.textConfig.text);
                        auto* theComponent = new ScriptComponent(funcCallback, ScriptType::SceneUpdate);
                        return theComponent;
                        break;
                    }

                case ScriptType::EntityUpdate:
                    {
                        auto funcCallback = app.GetScriptRegistry().FetchEntityUpdateScript(component.textConfig.text);
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

        throw std::runtime_error("Component type not found");
    }

    /**
     * This should only be called when creating/Making entities or components since this will call
     * new on them.
     */
    std::unordered_map<std::string, Component*> ComponentLoader::CollectComponents(const std::vector<YComponent>& components, Application& app)
    {
        std::unordered_map<std::string, Component*> componentsForScene;

        for (auto& yComp : components)
        {
            componentsForScene.emplace(yComp.type, MakeComponentReal(yComp, app));
        }

        return componentsForScene;
    }
}