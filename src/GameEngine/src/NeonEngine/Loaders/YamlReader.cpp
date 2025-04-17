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
    void YamlReader::Read(const std::string& filepath)
    {
        std::ifstream ifs(filepath);
        m_yamlRoot = fkyaml::node::deserialize(ifs);
    }

    SceneConfig YamlReader::Init() const
    {
        if (m_yamlRoot["scene"] == nullptr) {
            throw std::runtime_error("Missing 'scene' node in YAML.");
        }

        const auto& sceneNode = m_yamlRoot["scene"];

        std::vector<SceneShader> shaders;

        SceneConfig sceneConfig;

        sceneConfig.audioPath = m_yamlRoot["scene"]["audio"].get_value<std::string>();

        for (const auto& shaderNode : m_yamlRoot["scene"]["shaders"]) {
            SceneShader shader;

            shader.id = shaderNode["name"].get_value<std::string>();
            shader.dir = shaderNode["dir"].get_value<std::string>();
            shader.vertexShader = shaderNode["vertex"].get_value<std::string>();
            shader.fragShader = shaderNode["frag"].get_value<std::string>();

            shaders.push_back(shader);
        }

        sceneConfig.shaders = shaders;

        return sceneConfig;
    }
}
