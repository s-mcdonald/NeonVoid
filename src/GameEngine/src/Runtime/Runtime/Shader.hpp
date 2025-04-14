/**
 * {SourceHeader}
 */

#pragma once

#include <string>

#include <Runtime/Runtime/Backends/OpenGL/OpenGLHeaders.hpp>

namespace Neon
{
    class Shader
    {
        public:
            Shader(std::string, std::string);
            ~Shader() = default;

        public:
            void OnInit();
            void OnDelete();
            [[nodiscard]] uint32_t GetShaderProgramId() const;

        private:
            static std::string LoadShaderFromFile(const std::string&);
            static uint32_t CompileShader(const char* source, GLenum shaderType);
            static uint32_t CreateShaderProgram(const char* vertexSource, const char* fragmentSource);

        private:
            const std::string m_vertexSourcePath;
            const std::string m_fragmentSourcePath;
            uint32_t m_shaderId;
    };
}
