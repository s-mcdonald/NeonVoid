/**
 * {SourceHeader}
 */

#pragma once

#include <string>

namespace Neon
{
    class IShader;
    class ShaderFactory
    {
        public:
            ShaderFactory() = default;
            ~ShaderFactory() = default;
        public:
            IShader* CreateShader(std::string vertexPath, std::string fragmentPath);
    };
}

