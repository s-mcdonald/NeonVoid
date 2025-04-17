/**
 * {SourceHeader}
 */

#pragma once

#include <IntRuntime.hpp>

namespace Neon
{
    class ShaderFactory
    {
        public:
            ShaderFactory() = default;
            ~ShaderFactory() = default;
        public:
            IShader* CreateShader(std::string vertexPath, std::string fragmentPath);
    };
}

