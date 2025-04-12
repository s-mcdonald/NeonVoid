/**
 *
 */

#pragma once

#include <string>

namespace Neon
{
    class Shader
    {
        public:
            Shader(std::string, std::string);
            ~Shader();

        public:
            void OnInit();
            void OnDelete();
            [[nodiscard]] uint32_t GetShaderProgramId() const;

        private:
            static std::string LoadShaderFromFile(const std::string&);

        private:
            const std::string m_vertexSourcePath;
            const std::string m_fragmentSourcePath;
            uint32_t m_shaderId;
    };
}
