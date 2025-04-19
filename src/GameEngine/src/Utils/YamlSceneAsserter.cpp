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
        if (node["scene"] == nullptr) {
            throw std::runtime_error("Missing 'scene' node in YAML.");
        }

        if (node["scene"]["type"] == nullptr) {
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
                    // Components can have differing dependencies, so we need
                    // to validate each type.
                    if (component["type"].as_str() == "audio")
                    {
                        AssertValidateComponentTypeAudio(component["data"]);
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
    }
};
