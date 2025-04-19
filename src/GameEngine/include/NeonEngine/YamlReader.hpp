/**
 * {SourceHeader}
 */

#pragma once

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
            YScene Init() const;
        private:
            fkyaml::node m_yamlRoot{};
    };
}
