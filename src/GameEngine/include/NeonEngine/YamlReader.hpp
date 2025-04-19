/**
 * {SourceHeader}
 */

#pragma once

#include <string>

#include <fkYAML/node.hpp>

#include <NeonEngine/Types.hpp>

namespace Neon
{
    class YamlReader
    {
        public:
            YamlReader() = default;
            void Read(const std::string& filepath);
            YScene Init() const;

        private:
            static YComponent LoadComponent(const fkyaml::basic_node<>& value) ;

        private:
            fkyaml::node m_yamlRoot{};
    };
}
