/**
 *    ███╗   ██╗███████╗ ██████╗ ███╗   ██╗
 *    ████╗  ██║██╔════╝██╔═══██╗████╗  ██║
 *    ██╔██╗ ██║█████╗  ██║   ██║██╔██╗ ██║
 *    ██║╚██╗██║██╔══╝  ██║   ██║██║╚██╗██║
 *    ██║ ╚████║███████╗╚██████╔╝██║ ╚████║
 *    ╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═══╝
 * ========================================
 *                 NeonVoid
 *         A 2D Game Engine in C++
 * ----------------------------------------
 * License: MIT
 * Copyright (c) : 2024 Sam McDonald
 * Repository: https://github.com/s-mcdonald/NeonVoid
 */
#include <fstream>

#include <NeonRuntime/Backends/OpenGLShader.hpp>

namespace Neon
{
    OpenGLShader::OpenGLShader(std::string  vertexPath, std::string  fragmentPath)
        : m_vertexSourcePath(std::move(vertexPath))
        , m_fragmentSourcePath(std::move(fragmentPath))
    {
        // ..
    }

    void OpenGLShader::OnInit()
    {
        auto vertex_shader_source = LoadShaderFromFile(m_vertexSourcePath);
        auto frag_shader_source = LoadShaderFromFile(m_fragmentSourcePath);

        m_shaderId = OpenGLShader::CreateShaderProgram(vertex_shader_source.c_str(), frag_shader_source.c_str());
    }

    void OpenGLShader::OnDelete()
    {
        glDeleteProgram(m_shaderId);
        m_shaderId = 0;
    }

    // we want to bind all shaders before game loop
    void OpenGLShader::Bind() const
    {
        glUseProgram(m_shaderId);
    }

    // unbind after game loop
    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    uint32_t OpenGLShader::GetShaderProgramId() const
    {
        return m_shaderId;
    }

    // Loads from file
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
        uint32_t shader = glCreateShader(shaderType);
        const char* sourceCStr = source;
        glShaderSource(shader, 1, &sourceCStr, nullptr);
        glCompileShader(shader);

        // Check for compilation errors
        int success = 0;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::string compiledShaderType = (shaderType == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
            throw std::runtime_error(compiledShaderType + " Shader compilation failed: " + std::string(infoLog));
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
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
    }
}
