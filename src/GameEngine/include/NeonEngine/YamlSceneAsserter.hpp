/**
 * {SourceHeader}
 */

#pragma once

#include <stdexcept>
#include <unordered_map>
#include <string>

#include <fkYAML/node.hpp>

#include <NeonEngine/Types.hpp>
#include <NeonEngine/SceneTypeConverter.hpp>

namespace Neon
{
    class YamlSceneAsserter
    {
        public:
            static void AssertValidYaml(const fkyaml::node& node);
            static void AssertSceneTypeYaml(const fkyaml::basic_node<>& value);
            static void AssertSceneComponentsYaml(const fkyaml::basic_node<>& value);
            static void AssertSceneEntitiesYaml(const fkyaml::basic_node<>& value);

            static void AssertValidateComponentTypeAudio(const fkyaml::basic_node<>& value);
    };
}
