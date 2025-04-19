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
                sceneComponent.audioConfig = new YAudioConfigData{};
                sceneComponent.audioConfig->path = component["data"]["path"].as_str();
                if (component["data"].contains("loop"))
                {
                    sceneComponent.audioConfig->loop = component["data"]["loop"].as_bool();
                }
            }

            if (sceneComponent.type == "position")
            {
                if (component.contains("data"))
                {
                    sceneComponent.posConfig = new YPosConfigData{};
                    sceneComponent.posConfig->p.x = component["data"]["initial"]["x"].as_float();
                    sceneComponent.posConfig->p.y = component["data"]["initial"]["y"].as_float();
                }
            }

            // sceneComponent.dir = shaderNode["dir"].get_value<std::string>();
            // shader.vertexShader = shaderNode["vertex"].get_value<std::string>();
            // shader.fragShader = shaderNode["frag"].get_value<std::string>();

            sceneConfig.components.push_back(sceneComponent);
        }

        return sceneConfig;
    }
}
