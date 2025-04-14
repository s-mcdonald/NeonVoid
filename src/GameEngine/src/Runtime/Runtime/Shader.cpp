/**
 * {SourceHeader}
 */

#include <fstream>
#include <sstream>
#include <string>
#include <utility>

#include <Runtime/Runtime.hpp>
#include <Runtime/Runtime/Backends/OpenGL/OpenGL.hpp>
#include <Runtime/Runtime/Shader.hpp>

namespace Neon
{
    Shader::Shader(std::string  vertexPath, std::string  fragmentPath)
        : m_vertexSourcePath(std::move(vertexPath))
        , m_fragmentSourcePath(std::move(fragmentPath))
    {
        //
    }

    void Shader::OnInit()
    {
        auto vertex_shader_source = LoadShaderFromFile(m_vertexSourcePath);
        auto frag_shader_source = LoadShaderFromFile(m_fragmentSourcePath);

        // abstract this to ogl layer
        m_shaderId = OpenGL::CreateShaderProgram(vertex_shader_source.c_str(), frag_shader_source.c_str());
    }

    void Shader::OnDelete()
    {
        // abstract this to ogl layer
        glDeleteProgram(m_shaderId);
        m_shaderId = 0;
    }

    uint32_t Shader::GetShaderProgramId() const
    {
        return m_shaderId;
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
