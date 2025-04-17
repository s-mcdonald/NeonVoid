/**
 * {SourceHeader}
 */

#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <fkYAML/node.hpp>

namespace Neon
{
    struct SceneShader
    {
        std::string id;
        std::string dir;
        std::string vertexShader;
        std::string fragShader;
    };

    class YamlReader
    {
        public:
            explicit YamlReader(const std::string& filepath);
            [[nodiscard]] std::vector<SceneShader> Load() const;

        private:
            fkyaml::node m_yamlRoot{};
    };
}
