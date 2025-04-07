#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

#include "../Runtime.hpp"
#include "Shader.hpp"

namespace Neon
{
    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
        : m_vertex_source_path(vertexPath)
        , m_fragment_source_path(fragmentPath)
    {
        //
    }

    Shader::~Shader()
    {
        //
    }

    void Shader::OnInit()
    {
        auto vertex_shader_source = LoadShaderFromFile(m_vertex_source_path);
        auto frag_shader_source = LoadShaderFromFile(m_fragment_source_path);

        m_shader_id = OpenGL::CreateShaderProgram(vertex_shader_source.c_str(), frag_shader_source.c_str());
    }

    void Shader::OnDelete()
    {
        // abstract this to ogl layer
        glDeleteProgram(m_shader_id);
        m_shader_id = 0;
    }

    GLuint Shader::GetShaderProgramId()
    {
        return m_shader_id;
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
