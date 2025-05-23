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

#pragma once

#include <string>

#include <NeonRuntime/Backends/OpenGLHeaders.hpp>
#include <NeonRuntime/IShader.hpp>

namespace Neon
{
    class OpenGLShader : public IShader
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
            void SetUniformMat4(std::string name, glm::mat4 value) override;

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
