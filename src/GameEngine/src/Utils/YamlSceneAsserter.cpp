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
#include <stdexcept>
#include <string>

#include <NeonEngine/EntityTypeConverter.hpp>
#include <NeonEngine/SceneTypeConverter.hpp>
#include <NeonEngine/YamlSceneAsserter.hpp>

namespace Neon
{
    void YamlSceneAsserter::AssertValidYaml(const fkyaml::node& node)
    {
        for (const auto& [parentKey, value] : node.map_items())
        {
            // Move string values to const later
            if (parentKey != "scene")
            {
                throw std::runtime_error("The parent value of the Yaml must be scene");
            }

            for (const auto& [sceneKey, sceneValue] : value.map_items())
            {
                if (sceneKey == "type")
                {
                    AssertSceneTypeYaml(sceneValue);
                }

                // gameplay is optional, so only assert if we have it
                if (sceneKey == "gameplay")
                {
                    AssertGamePlayYaml(sceneValue);
                }

                // fonts are required if you want to display text
                // ideally, I need to provide a default font so
                // it can be an optional key.
                if (sceneKey == "fonts")
                {
                    AssertFontsYaml(sceneValue);
                }

                if (sceneKey == "scripts")
                {
                    for (auto s : sceneValue.as_seq())
                    {
                        AssertValidateComponentTypeScript(s.as_map()["data"]);
                    }
                }

                if (sceneKey == "components")
                {
                    AssertComponentsSeqYaml(sceneValue);
                }

                if (sceneKey == "entities")
                {
                    AssertSceneEntitiesYaml(sceneValue);
                }
            }
        }

        if (node["scene"] == nullptr)
        {
            throw std::runtime_error("Missing 'scene' node in YAML.");
        }

        if (node["scene"]["type"] == nullptr)
        {
            throw std::runtime_error("Missing 'scene.type' node in YAML.");
        }
    }

    void YamlSceneAsserter::AssertComponentsSeqYaml(const fkyaml::basic_node<>& value)
    {
        if (value.is_sequence())
        {
            for (const auto& component : value)
            {
                if (false == component.contains("name"))
                {
                    throw std::runtime_error(".components.component MUST have a `name`");
                }

                if (false == component.contains("type"))
                {
                    throw std::runtime_error("*.components.component MUST have a `type`");
                }

                if (false == component["name"].is_string())
                {
                    throw std::runtime_error("*.components.component.name MUST be a `string`");
                }

                if (false == component["type"].is_string())
                {
                    throw std::runtime_error("*.components.component.type MUST be a `string`");
                }

                if (component.contains("data"))
                {
                    if (component["type"].as_str() == "audio")
                    {
                        AssertValidateComponentTypeAudio(component["data"]);
                    }

                    if (component["type"].as_str() == "position")
                    {
                        if (component.contains("data"))
                        {
                            AssertValidateComponentTypePosition(component["data"]);
                        }
                    }

                    if (component["type"].as_str() == "movement")
                    {
                        if (component.contains("data"))
                        {
                            AssertValidateComponentTypeMovement(component["data"]);
                        }
                    }

                    if (component["type"].as_str() == "shader")
                    {
                        AssertValidateComponentTypeShader(component["data"]);
                    }

                    if (component["type"].as_str() == "text")
                    {
                        if (component.contains("data"))
                        {
                            AssertValidateComponentTypeText(component["data"]);
                        }
                    }

                    if (component["type"].as_str() == "script")
                    {
                        if (component.contains("data"))
                        {
                            AssertValidateComponentTypeScript(component["data"]);
                        }
                    }

                    if (component["type"].as_str() == "collision")
                    {
                        AssertValidateComponentTypeCollision(component["data"]);
                    }

                    if (component["type"].as_str() == "timer")
                    {
                        AssertValidateComponentTypeTimer(component["data"]);
                    }
                }
            }

            return;
        }

        throw std::runtime_error("*.components Must be an array sequence value");
    }

    void YamlSceneAsserter::AssertSceneEntitiesYaml(const fkyaml::basic_node<>& value)
    {
        if (false == value.is_sequence())
        {
            throw std::runtime_error("scene.entities Must be an array sequence value");
        }

        for (const auto& entity : value)
        {
            // Access entity properties
            if (false == entity.contains("name"))
            {
                throw std::runtime_error("entities.entity Must contain a type.");
            }

            // Access entity properties
            if (false == entity.contains("type"))
            {
                throw std::runtime_error("entities.entity Must contain a type.");
            }

            AssertEntityTypeYaml(entity["type"]);

            // Access entity properties
            if (false == entity.contains("components"))
            {
                throw std::runtime_error("entities.entity Must have at least 1 component.");
            }

            AssertComponentsSeqYaml(entity["components"]);
        }
    }


    // Assert a value type of SceneType
    void YamlSceneAsserter::AssertSceneTypeYaml(const fkyaml::basic_node<>& value)
    {
        if (value.is_string())
        {
            if (SceneTypeConverter::IsValid(value.as_str()))
            {
                return;
            }

            throw std::runtime_error("component.audio has an invalid type.");
        }

        throw std::runtime_error("component.audio Must be a string value");
    }

    // Assert a value type of SceneType
    void YamlSceneAsserter::AssertEntityTypeYaml(const fkyaml::basic_node<>& value)
    {
        if (value.is_string())
        {
            if (EntityTypeConverter::IsValid(value.as_str()))
            {
                return;
            }

            throw std::runtime_error("entity.type has an invalid type.");
        }

        throw std::runtime_error("entity.type Must be a string value");
    }

    // This validates the Data sequence for Audio Type
    void YamlSceneAsserter::AssertValidateComponentTypeAudio(const fkyaml::basic_node<>& value)
    {
        if (false == value.is_mapping())
        {
            throw std::runtime_error("scene.components.component.audio.data MUST be a mapping value");
        }

        if (false == value.contains("path"))
        {
            throw std::runtime_error("scene.components.component.audio.data.path IS required.");
        }

        if (false == value["path"].is_string())
        {
            throw std::runtime_error("scene.components.component.audio.data.path MUST be a string.");
        }

        // Optional
        if (value.contains("loop"))
        {
            if (false == value["loop"].is_boolean())
            {
                throw std::runtime_error("scene.components.component.audio.data.loop MUST be a boolean value");
            }
        }

        // optional
        if (value.contains("volume"))
        {
            if (false == value["volume"].is_integer())
            {
                throw std::runtime_error("scene.components.component.audio.data.volume MUST be a integer value");
            }

            if (value["volume"].as_int() > 100 && value["volume"].as_int() < 0)
            {
                throw std::runtime_error("scene.components.component.audio.data.volume MUST be between 0-100");
            }
        }
    }

    // This validates the Data sequence for Position Type
    void YamlSceneAsserter::AssertValidateComponentTypePosition(const fkyaml::basic_node<>& value)
    {
        if (false == value.is_mapping())
        {
            throw std::runtime_error("scene.components.component.position.data MUST be a mapping value");
        }

        if (false == value.contains("initial"))
        {
            throw std::runtime_error("scene.components.component.position.data.initial IS required when providing data.");
        }

        if (false == value["initial"].contains("x"))
        {
            throw std::runtime_error("scene.components.component.position.data.initial.x must be provided");
        }

        if (false == value["initial"].contains("y"))
        {
            throw std::runtime_error("scene.components.component.position.data.initial.y must be provided");
        }

        if (false == value["initial"]["x"].is_float_number())
        {
            throw std::runtime_error("scene.components.component.position.data.initial.x must be a float");
        }

        if (false == value["initial"]["y"].is_float_number())
        {
            throw std::runtime_error("scene.components.component.position.data.initial.y must be a float");
        }
    }

    // This validates the Data sequence for shader Type
    void YamlSceneAsserter::AssertValidateComponentTypeShader(const fkyaml::basic_node<>& value)
    {
        if (false == value.is_mapping())
        {
            throw std::runtime_error("scene.components.component.shader.data MUST be a mapping value");
        }

        if (false == value.contains("name"))
        {
            throw std::runtime_error("scene.components.component.shader.data.name IS required");
        }

        if (false == value.contains("layer"))
        {
            throw std::runtime_error("scene.components.component.shader.data.layer IS required.");
        }

        if (false == value.contains("dir"))
        {
            throw std::runtime_error("scene.components.component.shader.data.dir IS required.");
        }

        if (false == value.contains("vertex"))
        {
            throw std::runtime_error("scene.components.component.shader.data.vertex IS required.");
        }

        if (false == value.contains("frag"))
        {
            throw std::runtime_error("scene.components.component.shader.data.frag IS required.");
        }

        if (false == value["name"].is_string())
        {
            throw std::runtime_error("scene.components.component.shader.data.name Must be a string");
        }

        if (false == value["layer"].is_string())
        {
            throw std::runtime_error("scene.components.component.shader.data.layer Must be a one of background|foreground");
        }

        if (false == value["dir"].is_string())
        {
            throw std::runtime_error("scene.components.component.shader.data.dir Must be a string");
        }

        if (false == value["vertex"].is_string())
        {
            throw std::runtime_error("scene.components.component.shader.data.vertex Must be a string");
        }

        if (false == value["frag"].is_string())
        {
            throw std::runtime_error("scene.components.component.shader.data.frag Must be a string");
        }

        if (false == value["vertices"].is_sequence())
        {
            throw std::runtime_error("scene.components.component.shader.data.vertices Must be a sequence");
        }
    }

    // This validates the Data sequence for Position Type
    void YamlSceneAsserter::AssertValidateComponentTypeMovement(const fkyaml::basic_node<>& value)
    {
        throw std::runtime_error("scene.components.component.movement.data SHOULD NOT be allowed.");
    }

    void YamlSceneAsserter::AssertValidateComponentTypeText(const fkyaml::basic_node<>& value)
    {
        if (false == value.is_mapping())
        {
            throw std::runtime_error("scene.components.component.text.data MUST be a mapping value");
        }

        if (false == value.contains("text"))
        {
            throw std::runtime_error("scene.components.component.text.data.text IS required");
        }
    }

    void YamlSceneAsserter::AssertValidateComponentTypeScript(const fkyaml::basic_node<>& value)
    {
        if (false == value.is_mapping())
        {
            throw std::runtime_error("script.data MUST be a mapping value");
        }

        if (false == value.contains("bind"))
        {
            throw std::runtime_error("script.data.bind IS required");
        }

        if (false == value["bind"].is_string())
        {
            throw std::runtime_error("script.data.bind MUST be a string");
        }
    }

    void YamlSceneAsserter::AssertValidateComponentTypeCollision(const fkyaml::basic_node<>& value)
    {
        if (false == value.is_mapping())
        {
            throw std::runtime_error("component.collision.data MUST be a mapping value");
        }

        if (false == value.contains("box"))
        {
            throw std::runtime_error("component.collision.data.box IS required");
        }

        if (false == value["box"].contains("x"))
        {
            throw std::runtime_error("component.collision.data.box.x must be provided");
        }

        if (false == value["box"].contains("y"))
        {
            throw std::runtime_error("component.collision.data.box.y must be provided");
        }

        if (false == value["box"]["x"].is_float_number())
        {
            throw std::runtime_error("component.collision.data.box.x must be a float");
        }

        if (false == value["box"]["y"].is_float_number())
        {
            throw std::runtime_error("component.collision.data.box.y must be a float");
        }
    }

    void YamlSceneAsserter::AssertValidateComponentTypeTimer(const fkyaml::basic_node<>& value)
    {
        if (false == value.is_mapping())
        {
            throw std::runtime_error("component.timer.data MUST be a mapping value");
        }

        if (false == value.contains("bind"))
        {
            throw std::runtime_error("component.timer.data.bind IS required");
        }

        if (false == value["bind"].is_string())
        {
            throw std::runtime_error("component.timer.data.bind MUST be a string");
        }
    }

    void YamlSceneAsserter::AssertGamePlayYaml(const fkyaml::basic_node<>& value)
    {
        if (false == value.is_mapping())
        {
            throw std::runtime_error("scene.gameplay MUST be a mapping value");
        }

        if (false == value.contains("config"))
        {
            throw std::runtime_error("scene.gameplay.config IS required");
        }

        if (false == value["config"].contains("enable_bonus"))
        {
            throw std::runtime_error("scene.gameplay.config.enable_bonus IS required");
        }

        if (false == value["config"].contains("enable_gravity"))
        {
            throw std::runtime_error("scene.gameplay.config.enable_gravity IS required");
        }

        if (false == value["config"].contains("enable_friction"))
        {
            throw std::runtime_error("scene.gameplay.config.enable_friction IS required");
        }

        if (false == value.contains("points"))
        {
            throw std::runtime_error("scene.gameplay.points IS required");
        }

        if (false == value["points"].contains("bonus"))
        {
            throw std::runtime_error("scene.gameplay.points.bonus IS required");
        }

        if (false == value["points"].contains("enemy_collision"))
        {
            throw std::runtime_error("scene.gameplay.points.enemy_collision IS required");
        }

        if (false == value["config"]["enable_bonus"].is_boolean())
        {
            throw std::runtime_error("scene.gameplay.config.enable_bonus MUST be an boolean");
        }

        if (false == value["config"]["enable_gravity"].is_boolean())
        {
            throw std::runtime_error("scene.gameplay.config.enable_gravity MUST be an boolean");
        }

        if (false == value["config"]["enable_friction"].is_boolean())
        {
            throw std::runtime_error("scene.gameplay.config.enable_friction MUST be an boolean");
        }

        if (false == value["points"]["bonus"].is_integer())
        {
            throw std::runtime_error("scene.gameplay.points.bonus MUST be an integer");
        }

        if (false == value["points"]["enemy_collision"].is_integer())
        {
            throw std::runtime_error("scene.gameplay.points.enemy_collision MUST be an integer");
        }
    }

    void YamlSceneAsserter::AssertFontsYaml(const fkyaml::basic_node<>& value)
    {
        if (false == value.is_sequence())
        {
            throw std::runtime_error("scene.gameplay MUST be a sequence value");
        }

        for (const auto& font : value)
        {
            if (false == font.contains("name"))
            {
                throw std::runtime_error("scene.fonts.font.name IS required");
            }

            if (false == font.contains("size"))
            {
                throw std::runtime_error("scene.fonts.font.size IS required");
            }

            if (false == font.contains("path"))
            {
                throw std::runtime_error("scene.fonts.font.path IS required");
            }
        }
    }
};
