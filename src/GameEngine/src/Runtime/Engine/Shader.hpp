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
            static GLuint Load(const std::string&, const std::string&);

        private:
            static std::string LoadShaderFromFile(const std::string&);
    };
}
