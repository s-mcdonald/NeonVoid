/**
 * {SourceHeader}
 */

#pragma once

#include <fkYAML/node.hpp>

namespace Neon
{
    class YamlSceneAsserter
    {
        public:
            static void AssertValidYaml(const fkyaml::node& node);

        protected:
            static void AssertSceneTypeYaml(const fkyaml::basic_node<>& value);
            static void AssertSceneComponentsYaml(const fkyaml::basic_node<>& value);
            static void AssertSceneEntitiesYaml(const fkyaml::basic_node<>& value);

            static void AssertValidateComponentTypeAudio(const fkyaml::basic_node<>& value);
            static void AssertValidateComponentTypePosition(const fkyaml::basic_node<>& value);
            static void AssertValidateComponentTypeMovement(const fkyaml::basic_node<>& value);
            static void AssertValidateComponentTypeShader(const fkyaml::basic_node<>& value);
            static void AssertValidateComponentTypeText(const fkyaml::basic_node<>& value);
    };
}
