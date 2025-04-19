/**
 * {SourceHeader}
 */

#include <iostream>
#include <fstream>
#include <string>

#include <fkYAML/node.hpp>

#include <NeonEngine/YamlReader.hpp>

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
        // Ensure the YAML coming in is valid and will throw
        // exception if not valid so we can
        // trust the object coming in.
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
            sceneConfig.components.push_back(LoadComponent(component));
        }

        for (const auto& entity : sceneNode["entities"])
        {
            YEntity sceneEntity;

            sceneEntity.name = entity["name"].as_str();

            for (const auto& component : entity["components"])
            {
                sceneEntity.components.push_back(LoadComponent(component));
            }

            sceneConfig.entities.push_back(sceneEntity);
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
            yComponent.configType = YComponent::ConfigType::Audio;
            yComponent.audioConfig = new YAudioConfigData{};
            yComponent.audioConfig->path = value["data"]["path"].as_str();
            if (value["data"].contains("loop"))
            {
                yComponent.audioConfig->loop = value["data"]["loop"].as_bool();
            }

            // by default at 50 for all
            yComponent.audioConfig->volume = 50;

            if (value["data"].contains("volume"))
            {
                yComponent.audioConfig->volume = value["data"]["volume"].as_int();
            }
        }

        if (yComponent.type == "movement")
        {
            yComponent.configType = YComponent::ConfigType::Movement;
            // Movement does not have data
        }

        if (yComponent.type == "position")
        {
            yComponent.configType = YComponent::ConfigType::Position;
            if (value.contains("data"))
            {
                yComponent.posConfig = new YPosConfigData{};
                yComponent.posConfig->p.x = value["data"]["initial"]["x"].as_float();
                yComponent.posConfig->p.y = value["data"]["initial"]["y"].as_float();
            }
        }

        if (yComponent.type == "shader")
        {
            yComponent.configType = YComponent::ConfigType::Shader;
            yComponent.shaderConfig = new YShader{};
            yComponent.shaderConfig->name = value["data"]["name"].as_str();
            yComponent.shaderConfig->layer = value["data"]["layer"].as_str();
            yComponent.shaderConfig->dir = value["data"]["dir"].as_str();
            yComponent.shaderConfig->vertexShader = value["data"]["vertex"].as_str();
            yComponent.shaderConfig->fragShader = value["data"]["frag"].as_str();
        }

        return yComponent;
    }
}
