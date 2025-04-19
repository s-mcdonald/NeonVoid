/**
 * {SourceHeader}
 */

#include <stdexcept>
#include <unordered_map>
#include <string>

#include <NeonEngine/Types.hpp>
#include <NeonEngine/SceneTypeConverter.hpp>
#include <NeonEngine/YamlSceneAsserter.hpp>

namespace Neon
{
    // Runtime Assert
    // Assertion Entry
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
        if (node["scene"] == nullptr)
        {
            throw std::runtime_error("Missing 'scene' node in YAML.");
        }

        if (node["scene"]["type"] == nullptr)
        {
            throw std::runtime_error("Missing 'scene.type' node in YAML.");
        }
    }

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

        throw std::runtime_error("scene.audio Must be a string value");
    }

    void YamlSceneAsserter::AssertSceneComponentsYaml(const fkyaml::basic_node<>& value)
    {
        if (value.is_sequence())
        {
            for (const auto& component : value)
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
                }
            }

            return;
        }

        throw std::runtime_error("scene.components Must be an array sequence value");
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
                throw std::runtime_error("scene.entities Must be an array sequence value");
            }

            // Access entity properties
            if (false == entity.contains("components"))
            {
                throw std::runtime_error("scene.entities.entity Must have at least 1 component.");
            }

            AssertSceneComponentsYaml(entity["components"]);
        }
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

    }

    // This validates the Data sequence for Position Type
    void YamlSceneAsserter::AssertValidateComponentTypeMovement(const fkyaml::basic_node<>& value)
    {
        throw std::runtime_error("scene.components.component.movement.data SHOULD NOT be allowed.");
    }
};
