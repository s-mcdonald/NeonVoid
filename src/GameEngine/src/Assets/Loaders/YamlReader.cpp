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

        std::cout << filepath << std::endl;
        // std::cout << m_yamlRoot << std::endl;
    }

    YScene YamlReader::Init() const
    {
        YamlSceneAsserter::AssertValidYaml(m_yamlRoot);

        const auto& sceneNode = m_yamlRoot["scene"];

        YScene sceneConfig;

        std::vector<YShader> shaders;
        std::vector<YEntity> entities;
        std::vector<YComponent> scene_components;
        std::vector<YComponent> entity_components;

        sceneConfig.sceneType = SceneTypeConverter::Parse(sceneNode["type"].as_str());

        for (const auto& component : sceneNode["components"])
        {
            sceneConfig.components.emplace_back(LoadComponent(component));
        }

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
            yComponent.textConfig.text = value["data"]["on_update"].as_str();
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
