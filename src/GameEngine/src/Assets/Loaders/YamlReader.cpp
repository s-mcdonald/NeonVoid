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

#include <fstream>
#include <iostream>
#include <string>

#include <fkYAML/node.hpp>

#include <NeonEngine/YamlReader.hpp>
#include "NeonEngine/EntityTypeConverter.hpp"
#include "NeonEngine/SceneTypeConverter.hpp"
#include "NeonEngine/YamlSceneAsserter.hpp"

namespace Neon
{
    void YamlReader::Read(const std::string& filepath)
    {
        std::ifstream ifs(filepath);
        m_yamlRoot = fkyaml::node::deserialize(ifs);
    }

    YScene YamlReader::Init() const
    {
        YamlSceneAsserter::AssertValidYaml(m_yamlRoot);

        const auto& sceneNode = m_yamlRoot["scene"];

        YScene sceneConfig;

        sceneConfig.sceneType = SceneTypeConverter::Parse(sceneNode["type"].as_str());

        ///
        /// GAMEPLAY
        ///
        if (sceneNode.contains("gameplay"))
        {
            sceneConfig.gamePlay.enable_bonus = sceneNode["gameplay"]["config"]["enable_bonus"].as_bool();
            sceneConfig.gamePlay.enable_gravity = sceneNode["gameplay"]["config"]["enable_gravity"].as_bool();
            sceneConfig.gamePlay.enable_friction = sceneNode["gameplay"]["config"]["enable_friction"].as_bool();
            sceneConfig.gamePlay.bonus = sceneNode["gameplay"]["points"]["bonus"].as_int();
            sceneConfig.gamePlay.enemy_collision = sceneNode["gameplay"]["points"]["enemy_collision"].as_int();
        }
        else
        {
            // defaults
            sceneConfig.gamePlay.enable_bonus = false;
            sceneConfig.gamePlay.enable_gravity = false;
            sceneConfig.gamePlay.enable_friction = false;
            sceneConfig.gamePlay.bonus = 0;
            sceneConfig.gamePlay.enemy_collision = 0;
        }

        ///
        /// FONTS
        ///
        if (sceneNode.contains("fonts"))
        {
            for (auto& font : sceneNode["fonts"])
            {
                sceneConfig.fonts.name = font["name"].as_str();
                sceneConfig.fonts.path = font["path"].as_str();
                sceneConfig.fonts.size = font["size"].as_float();
                // hack exit for now since we can only load the first font
                break;
            }
        }


        ///
        /// SCRIPTS
        ///
        for (const auto& scripts : sceneNode["scripts"])
        {
            sceneConfig.scripts.emplace_back(LoadComponent(scripts));
        }

        ///
        /// COMPONENTS
        ///
        for (const auto& component : sceneNode["components"])
        {
            sceneConfig.components.emplace_back(LoadComponent(component));
        }

        ///
        /// ENTITIES
        ///
        for (const auto& entity : sceneNode["entities"])
        {
            YEntity sceneEntity;

            sceneEntity.name = entity["name"].as_str();
            sceneEntity.type = EntityTypeConverter::Parse(entity["type"].as_str());

            for (const auto& component : entity["components"])
            {
                sceneEntity.components.emplace_back(LoadComponent(component));
            }

            sceneConfig.entities.emplace_back(sceneEntity);
        }

        return sceneConfig;
    }

    YComponent YamlReader::LoadComponent(const fkyaml::basic_node<>& value)
    {
        YComponent yComponent;

        yComponent.name = value["name"].as_str();
        yComponent.type = value["type"].as_str();

        if (yComponent.type == "audio")
        {
            yComponent.configType = ConfigType::Audio;
            yComponent.audioConfig = new YAudioConfigData{};
            yComponent.audioConfig->path = value["data"]["path"].as_str();
            if (value["data"].contains("loop"))
            {
                yComponent.audioConfig->loop = value["data"]["loop"].as_bool();
            }

            yComponent.audioConfig->volume = DefaultAudioVolume;

            if (value["data"].contains("volume"))
            {
                yComponent.audioConfig->volume = value["data"]["volume"].as_int();
            }
        }

        if (yComponent.type == "movement")
        {
            yComponent.configType = ConfigType::Movement;
            // Movement does not have data
        }

        if (yComponent.type == "position")
        {
            yComponent.configType = ConfigType::Position;
            if (value.contains("data"))
            {
                yComponent.posConfig = new YPosConfigData{};
                yComponent.posConfig->p.x = value["data"]["initial"]["x"].as_float();
                yComponent.posConfig->p.y = value["data"]["initial"]["y"].as_float();
            }
        }

        if (yComponent.type == "text")
        {
            yComponent.configType = ConfigType::Text;

            yComponent.textConfig;
            yComponent.textConfig.text = value["data"]["text"].as_str();
        }

        if (yComponent.type == "script")
        {
            yComponent.configType = ConfigType::Script;

            yComponent.textConfig;
            yComponent.textConfig.text = value["data"]["bind"].as_str();
        }

        if (yComponent.type == "shader")
        {
            yComponent.configType = ConfigType::Shader;
            yComponent.shaderConfig = new YShader{};
            yComponent.shaderConfig->name = value["data"]["name"].as_str();
            yComponent.shaderConfig->layer = value["data"]["layer"].as_str();
            yComponent.shaderConfig->dir = value["data"]["dir"].as_str();
            yComponent.shaderConfig->vertexShader = value["data"]["vertex"].as_str();
            yComponent.shaderConfig->fragShader = value["data"]["frag"].as_str();

            std::vector<float> vertices;
            for (const auto& vertex : value["data"]["vertices"].as_seq())
            {
                auto vertexData = vertex.as_seq();
                vertices.push_back(vertexData[0].as_float());
                vertices.push_back(vertexData[1].as_float());
                vertices.push_back(vertexData[2].as_float());
                vertices.push_back(vertexData[3].as_float());
                vertices.push_back(vertexData[4].as_float());
            }

            yComponent.shaderConfig->vertices = vertices;
        }

        if (yComponent.type == "collision")
        {
            yComponent.configType = ConfigType::Position;
            if (value.contains("data"))
            {
                yComponent.posConfig = new YPosConfigData{};
                yComponent.posConfig->p.x = value["data"]["box"]["x"].as_float();
                yComponent.posConfig->p.y = value["data"]["box"]["y"].as_float();
            }
        }

        return yComponent;
    }
}
