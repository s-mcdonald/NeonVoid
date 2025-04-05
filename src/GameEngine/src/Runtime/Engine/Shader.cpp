#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

#include "../Runtime.hpp"
#include "Shader.hpp"

namespace Neon
{
    GLuint Shader::Load(const std::string& vertexPath, const std::string& fragmentPath)
    {
        auto vertex_shader_source = LoadShaderFromFile(vertexPath);
        auto frag_shader_source = LoadShaderFromFile(fragmentPath);

        return OpenGL::CreateShaderProgram(vertex_shader_source.c_str(), frag_shader_source.c_str());
    }

    std::string Shader::LoadShaderFromFile(const std::string& filePath)
    {
        std::ifstream file(filePath, std::ios::in | std::ios::binary);
        if (!file)
        {
            throw std::runtime_error("Error: Could not open shader file at path: " + filePath);
        }

        file.seekg(0, std::ios::end);
        size_t fileSize = static_cast<size_t>(file.tellg());
        file.seekg(0, std::ios::beg);

        std::string shaderCode;
        shaderCode.reserve(fileSize);
        shaderCode.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

        if (shaderCode.empty())
        {
            throw std::runtime_error("Error: Shader file is empty: " + filePath);
        }

        return shaderCode;
    }
}
