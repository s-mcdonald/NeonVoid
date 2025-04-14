/**
 * {SourceHeader}
 */

#include <fstream>
#include <sstream>
#include <string>
#include <utility>

#include <Runtime/Runtime.hpp>
#include <Runtime/Runtime/Backends/OpenGL/OpenGLHeaders.hpp>
#include <Runtime/Runtime/Backends/OpenGL/OpenGLShader.hpp>

namespace Neon
{
    OpenGLShader::OpenGLShader(std::string  vertexPath, std::string  fragmentPath)
        : m_vertexSourcePath(std::move(vertexPath))
        , m_fragmentSourcePath(std::move(fragmentPath))
    {
        //
    }

    void OpenGLShader::OnInit()
    {
        auto vertex_shader_source = LoadShaderFromFile(m_vertexSourcePath);
        auto frag_shader_source = LoadShaderFromFile(m_fragmentSourcePath);

        // abstract this to ogl layer
        m_shaderId = OpenGLShader::CreateShaderProgram(vertex_shader_source.c_str(), frag_shader_source.c_str());
    }

    void OpenGLShader::OnDelete()
    {
        // abstract this to ogl layer
        glDeleteProgram(m_shaderId);
        m_shaderId = 0;
    }

    uint32_t OpenGLShader::GetShaderProgramId() const
    {
        return m_shaderId;
    }

    std::string OpenGLShader::LoadShaderFromFile(const std::string& filePath)
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

    uint32_t OpenGLShader::CompileShader(const char* source, GLenum shaderType)
    {
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);

#if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cerr << "Shader compilation failed: " << infoLog << std::endl;
#endif
        }
        return shader;
    }

    uint32_t OpenGLShader::CreateShaderProgram(const char* vertexSource, const char* fragmentSource)
    {
        GLuint vertexShader = OpenGLShader::CompileShader(vertexSource, GL_VERTEX_SHADER);
        GLuint fragmentShader = OpenGLShader::CompileShader(fragmentSource, GL_FRAGMENT_SHADER);

        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        GLint success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);

#if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cerr << "Program linking failed: " << infoLog << std::endl;
#endif
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
    }
}
