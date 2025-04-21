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
#include <iostream>
#include <unordered_map>

#include <NeonEngine/Types.hpp>
#include <NeonEngine/ComponentLoader.hpp>
#include <NeonEngine/Components.hpp>
#include <NeonEngine/FunctionRegistry.hpp>
#include <NeonEngine/RuntimeBridge.hpp>

namespace Neon
{
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

                componentsForScene.emplace(comp.name, theComponent);
            }

            if (comp.type == "position")
            {
                // @todo, make PosComp accept point so we can pass initial
                auto* theComponent = new PositionComponent();
                componentsForScene.emplace(comp.name, theComponent);
            }

            if (comp.type == "movement")
            {
                // @todo, add data: key bindings
                auto* theComponent = new MovementComponent();
                componentsForScene.emplace(comp.name, theComponent);
            }

            if (comp.type == "shader")
            {
                auto vertexPath = comp.shaderConfig->dir + comp.shaderConfig->vertexShader;
                auto fragPath = comp.shaderConfig->dir + comp.shaderConfig->fragShader;

                auto shaderPgm = bridge.CreateShader(vertexPath,fragPath);

                // @todo, make PosComp accept point so we can pass initial
                auto* theComponent = new ShaderComponent(comp.shaderConfig->vertices, shaderPgm);

                componentsForScene.emplace(comp.name, theComponent);
            }

            if (comp.type == "text")
            {
                // built-in shader for text
                auto vertexPath = "/home/sam/Game/Neon/build/assets/shaders/Text/shader.vert";
                auto fragPath = "/home/sam/Game/Neon/build/assets/shaders/Text/shader.frag";

                auto shaderPgm = bridge.CreateShader(vertexPath,fragPath);
                auto* theComponent = new TextComponent(comp.textConfig.text, shaderPgm);
                componentsForScene.emplace(comp.name, theComponent);
            }

            if (comp.type == "script")
            {
                std::function<void(Scene* scene)> funcCallback = FunctionRegistry::Get().Fetch(comp.textConfig.text);
                auto* theComponent = new ScriptComponent(funcCallback);
                componentsForScene.emplace(comp.name, theComponent);
            }
        }

        return componentsForScene;
    }
}
