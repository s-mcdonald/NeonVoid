/**
 * {SourceHeader}
 */

#include <iostream>
#include <fstream>
#include <string>

#include <fkYAML/node.hpp>

#include <NeonEngine/YamlReader.hpp>

#include "NeonEngine/SceneTypeConverter.hpp"

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
                throw std::runtime_error("The parent value of the Yaml must be scene");
            }

            for (const auto& [sceneKey, sceneValue] : value.map_items())
            {
                if (sceneKey == "type")
                {
                    AssertSceneTypeYaml(sceneValue);
                }

                if (sceneKey == "components")
                {
                    AssertSceneComponentsYaml(sceneValue);
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

    void YamlReader::AssertSceneTypeYaml(const fkyaml::basic_node<>& value)
    {
        if (value.is_string())
        {
            std::cout << "Scene::Type: " << value.as_str() << std::endl;

            if (SceneTypeConverter::IsValid(value.as_str()))
            {
                return;
            }

            throw std::runtime_error("component.audio has an invalid type.");
        }

        throw std::runtime_error("scene.audio Must be a string value");
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

    void YamlReader::AssertSceneComponentsYaml(const fkyaml::basic_node<>& value)
    {
        if (value.is_sequence())
        {
            std::cout << "\n--- Components --- " << std::endl;
            for (const auto& component : value)
            {
                AssertSceneComponentCoreYaml(component);

                std::cout << "Component: " << std::endl;
                std::cout << " - name: " << component["name"].as_str() << std::endl;
                std::cout << " - type: " << component["type"].as_str() << std::endl;

                if (component.contains("data"))
                {
                    // Components can have differing dependencies, so we need
                    // to validate each type.
                    if (component["type"].as_str() == "audio")
                    {
                        AssertValidateComponentAudioType(component["data"]);
                    }

                    // if we dont throw then we are good.

                    std::cout << " - data: "  << std::endl;
                    // If you want to see all keys/values in each entity
                    for (const auto& [key, val] : component["data"].map_items())
                    {
                        std::cout << "\tKey: " << key.get_value<std::string>()
                                 << ", [Type: " << to_string(val.get_type()) << "] "<< std::endl;
                    }
                }
            }

            return;
        }

        throw std::runtime_error("scene.components Must be an array sequence value");
    }

    void YamlReader::AssertSceneComponentCoreYaml(const fkyaml::basic_node<>& component)
    {
        if (false == component.contains("name"))
        {
            throw std::runtime_error("scene.components.component MUST have a `name`");
        }

        if (false == component.contains("type"))
        {
            throw std::runtime_error("scene.components.component MUST have a `type`");
        }

        if (false == component["name"].is_string())
        {
            throw std::runtime_error("scene.components.component.name MUST be a `string`");
        }

        if (false == component["type"].is_string())
        {
            throw std::runtime_error("scene.components.component.type MUST be a `string`");
        }
    }

    void YamlReader::AssertSceneEntitiesYaml(const fkyaml::basic_node<>& value)
    {
        if (value.is_sequence())
        {
            std::cout << "\n--- Entities --- " << std::endl;
            for (const auto& entity : value)
            {
                // Access entity properties
                if (entity.contains("name"))
                {
                    std::cout << "Entity name: " << entity["name"].get_value<std::string>() << std::endl;
                }

                // If you want to see all keys/values in each entity
                for (const auto& [key, val] : entity.map_items())
                {
                    std::cout << "\tKey: " << key.get_value<std::string>()
                             << ", [Type: " << to_string(val.get_type()) << "] " << std::endl;
                }
            }

            return;
        }

       throw std::runtime_error("scene.entities Must be an array sequence value");
    }

    // This validates the Data sequence for Audio Type
    void YamlReader::AssertValidateComponentAudioType(const fkyaml::basic_node<>& value)
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
    }
}
