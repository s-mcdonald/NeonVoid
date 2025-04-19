/**
 * {SourceHeader}
 */

#include <iostream>
#include <fstream>
#include <string>

#include <fkYAML/node.hpp>

#include <NeonEngine/YamlReader.hpp>

namespace Neon
{
    void YamlReader::Read(const std::string& filepath)
    {
        std::ifstream ifs(filepath);
        m_yamlRoot = fkyaml::node::deserialize(ifs);
    }

    // void MoveablePlayerEntity::OnInit()
    // {
    //     // auto* positionComponent = new PositionComponent(0.0f, 0.0f);
    //     // AddComponent(positionComponent);
    //     //
    //     // auto* movementComponent = new MovementComponent();
    //     // movementComponent->AllowMovementOf(positionComponent); // change to using events instead
    //     // AddComponent(movementComponent);
    // }

    SceneConfig YamlReader::Init() const
    {
        // Ensure the YAML coming in is valid and will throw
        // exception if not valid so we can
        // trust the object coming in.
        AssertValidYaml(m_yamlRoot);

        const auto& sceneNode = m_yamlRoot["scene"];


        // for (const auto& element : sceneNode) {
        //     if (element.is_string())
        //     {
        //         std::cout << element.as_str() << " " << std::endl;
        //     }
        //
        //     if (element.is_boolean())
        //     {
        //         auto& key = "";
        //         if (element.has_tag_name())
        //         {
        //             std::cout <<  element.get_tag_name() << ":"  << std::endl;
        //         }
        //         else if (element.has_anchor_name())
        //         {
        //             std::cout <<  element.get_anchor_name() << ":"  << std::endl;
        //         }
        //
        //         std::cout <<  element.as_bool() << " " << std::endl;
        //     }
        //
        // }
        std::cout << std::endl;


        std::vector<YShader> shaders;

        SceneConfig sceneConfig;

        sceneConfig.audioPath = m_yamlRoot["scene"]["audio"].get_value<std::string>();
        sceneConfig.sceneType = m_yamlRoot["scene"]["type"].get_value<std::string>();

        for (const auto& shaderNode : m_yamlRoot["scene"]["shaders"])
        {
            YShader shader;

            shader.id = shaderNode["name"].get_value<std::string>();
            shader.dir = shaderNode["dir"].get_value<std::string>();
            shader.vertexShader = shaderNode["vertex"].get_value<std::string>();
            shader.fragShader = shaderNode["frag"].get_value<std::string>();

            shaders.push_back(shader);
        }

        sceneConfig.shaders = shaders;

        return sceneConfig;
    }

    // Runtime Assert
    void YamlReader::AssertValidYaml(const fkyaml::node& node) const
    {
        for (const auto& [parentKey, value] : m_yamlRoot.map_items())
        {
            // Move string values to const later
            if (parentKey != "scene") {
                throw std::runtime_error("The first Parent value of the Yaml must be scene");
            }

            for (const auto& [sceneKey, sceneValue] : value.map_items())
            {
                if (sceneKey == "audio")
                {
                    AssertSceneAudioYaml(sceneValue);
                }

                if (sceneKey == "audio_loop")
                {
                    AssertSceneAudioLoopYaml(sceneValue);
                }

                if (sceneKey == "entities")
                {
                    AssertSceneEntitiesYaml(sceneValue);
                }
            }
        }

        // Sanity check
        if (m_yamlRoot["scene"] == nullptr) {
            throw std::runtime_error("Missing 'scene' node in YAML.");
        }

        if (m_yamlRoot["scene"]["type"] == nullptr) {
            throw std::runtime_error("Missing 'scene.type' node in YAML.");
        }
    }

    void YamlReader::AssertSceneAudioYaml(const fkyaml::basic_node<>& value)
    {
        if (value.is_string())
        {
            std::cout << value.as_str() << std::endl;
            return;
        }

        throw std::runtime_error("scene.audio Must be a string value");
    }

    void YamlReader::AssertSceneAudioLoopYaml(const fkyaml::basic_node<>& value)
    {
        if (value.is_boolean())
        {
            std::cout << value.as_bool() << std::endl;
            return;
        }

        throw std::runtime_error("scene.audio_loop Must be a boolean value");
    }

    void YamlReader::AssertSceneEntitiesYaml(const fkyaml::basic_node<>& value)
    {
        //
    }
}
