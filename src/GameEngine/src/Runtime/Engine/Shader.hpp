/**
 *
 */

#pragma once

#include <GL/glew.h>
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
            GLuint GetShaderProgramId();

        private:
            static std::string LoadShaderFromFile(const std::string&);

        private:
            const std::string m_vertex_source_path;
            const std::string m_fragment_source_path;
            GLuint m_shader_id;
    };
}
