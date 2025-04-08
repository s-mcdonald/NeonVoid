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
            Shader(const std::string& vertexPath, const std::string& fragmentPath);
            ~Shader();

        public:
            void OnInit();
            void OnDelete();
            [[nodiscard]] uint32_t GetShaderProgramId() const;

        private:
            static std::string LoadShaderFromFile(const std::string&);

        private:
            const std::string m_vertex_source_path;
            const std::string m_fragment_source_path;
            uint32_t m_shader_id;
    };
}
