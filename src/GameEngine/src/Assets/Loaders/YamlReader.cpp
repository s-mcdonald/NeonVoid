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
            YComponent sceneComponent;

            sceneComponent.name = component["name"].as_str();
            sceneComponent.type = component["type"].as_str();

            if (sceneComponent.type == "audio")
            {
                sceneComponent.configType = YComponent::ConfigType::Audio;
                sceneComponent.audioConfig = new YAudioConfigData{};
                sceneComponent.audioConfig->path = component["data"]["path"].as_str();
                if (component["data"].contains("loop"))
                {
                    sceneComponent.audioConfig->loop = component["data"]["loop"].as_bool();
                }
            }

            if (sceneComponent.type == "movement")
            {
                sceneComponent.configType = YComponent::ConfigType::Movement;
                // Movement does not have data
            }

            if (sceneComponent.type == "position")
            {
                sceneComponent.configType = YComponent::ConfigType::Position;
                if (component.contains("data"))
                {
                    sceneComponent.posConfig = new YPosConfigData{};
                    sceneComponent.posConfig->p.x = component["data"]["initial"]["x"].as_float();
                    sceneComponent.posConfig->p.y = component["data"]["initial"]["y"].as_float();
                }
            }

            if (sceneComponent.type == "shader")
            {
                sceneComponent.configType = YComponent::ConfigType::Shader;
                sceneComponent.shaderConfig = new YShader{};
                sceneComponent.shaderConfig->name = component["data"]["name"].as_str();
                sceneComponent.shaderConfig->layer = component["data"]["layer"].as_str();
                sceneComponent.shaderConfig->dir = component["data"]["dir"].as_str();
                sceneComponent.shaderConfig->vertexShader = component["data"]["vertex"].as_str();
                sceneComponent.shaderConfig->fragShader = component["data"]["frag"].as_str();
            }

            sceneConfig.components.push_back(sceneComponent);
        }

        return sceneConfig;
    }
}
