/**
 * {SourceHeader}
 */

#include <iostream>
#include <fstream>
#include <string>

#include <fkYAML/node.hpp>

#include "YamlReader.hpp"

namespace Neon
{
    YamlReader::YamlReader(const std::string& filepath)
    {
        std::ifstream ifs(filepath);
        m_yamlRoot = fkyaml::node::deserialize(ifs);
    }

    std::vector<SceneShader> YamlReader::Load() const
    {
        std::vector<SceneShader> shaders;

        for (const auto& shaderNode : m_yamlRoot["shaders"]) {
            SceneShader shader;
            shader.id = shaderNode["name"].get_value<std::string>();
            shader.dir = shaderNode["dir"].get_value<std::string>();
            shader.vertexShader = shaderNode["vertex"].get_value<std::string>();
            shader.fragShader = shaderNode["frag"].get_value<std::string>();

            std::cout << "---------------------------------------" << std::endl;
            std::cout << shader.id << std::endl;
            std::cout << shader.dir << std::endl;
            std::cout << shader.vertexShader << std::endl;
            std::cout << shader.fragShader << std::endl;
            std::cout << "---------------------------------------" << std::endl;

            shaders.push_back(shader);
        }

        return shaders;
    }
}
