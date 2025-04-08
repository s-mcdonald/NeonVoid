#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

#include <Runtime/Runtime.hpp>
#include <Runtime/Engine/Backends/OpenGL/OpenGL.hpp>
#include <Runtime/Engine/Shader.hpp>
#include <utility>

namespace Neon
{
    Shader::Shader(std::string  vertexPath, std::string  fragmentPath)
        : m_vertex_source_path(std::move(vertexPath))
        , m_fragment_source_path(std::move(fragmentPath))
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

    uint32_t Shader::GetShaderProgramId() const
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
