/**
 * {SourceHeader}
 */

#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <NeonEngine/Types.hpp>
#include <fkYAML/node.hpp>

namespace Neon
{
    class YamlReader
    {
        public:
            YamlReader() = default;
            void Read(const std::string& filepath);
            SceneConfig Init() const;

        protected:
            void AssertValidYaml(const fkyaml::node& node) const;
            static void AssertSceneTypeYaml(const fkyaml::basic_node<>& value);
            static void AssertSceneAudioYaml(const fkyaml::basic_node<>& value);
            static void AssertSceneAudioLoopYaml(const fkyaml::basic_node<>& value);
            static void AssertSceneComponentsYaml(const fkyaml::basic_node<>& value);
            static void AssertSceneComponentCoreYaml(const fkyaml::basic_node<>& value);
            static void AssertSceneEntitiesYaml(const fkyaml::basic_node<>& value);

            static void AssertValidateComponentAudioType(const fkyaml::basic_node<>& value);

        private:
            fkyaml::node m_yamlRoot{};
    };
}
