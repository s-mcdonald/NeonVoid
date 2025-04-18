/**
 * {SourceHeader}
 */

#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <Types.hpp>
#include <fkYAML/node.hpp>

namespace Neon
{
    class YamlReader
    {
        public:
            YamlReader() = default;
            void Read(const std::string& filepath);
            SceneConfig Init() const;

        private:
            fkyaml::node m_yamlRoot{};
    };
}
