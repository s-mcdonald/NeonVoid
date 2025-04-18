/**
 * {SourceHeader}
 */

#pragma once

#include <string>

namespace Neon
{
    class IVertexBuffer;
    class IShader;
    class BufferFactory
    {
        public:
            BufferFactory() = default;
            ~BufferFactory() = default;
        public:
            IVertexBuffer* CreateVertexBuffer(float* vertices, size_t size) ;
            IShader* CreateShader(std::string vertexPath, std::string fragmentPath);
    };
}

