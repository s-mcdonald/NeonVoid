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
            explicit YamlReader(const std::string& filepath);
            SceneConfig Load() const;

        private:
            fkyaml::node m_yamlRoot{};
    };
}
