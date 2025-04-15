/**
 * {SourceHeader}
 */

#pragma once

#include <cstdint>
#include <string>

#include <Runtime/Backends/OpenGL/OpenGLHeaders.hpp>
#include <Runtime/Backends/Shader.hpp>

namespace Neon
{
    class OpenGLShader : public Shader
    {
        public:
            OpenGLShader() = default;
            OpenGLShader(std::string, std::string);
            ~OpenGLShader() override = default;

        public:
            void OnInit() override;
            void OnDelete() override;
            [[nodiscard]] uint32_t GetShaderProgramId() const override;

        public:
            void Bind() const override;
            void Unbind() const override;

        private:
            static std::string LoadShaderFromFile(const std::string&);
            static uint32_t CompileShader(const char* source, GLenum shaderType);
            static uint32_t CreateShaderProgram(const char* vertexSource, const char* fragmentSource);

        private:
            const std::string m_vertexSourcePath;
            const std::string m_fragmentSourcePath;
            uint32_t m_shaderId{};
    };
}
