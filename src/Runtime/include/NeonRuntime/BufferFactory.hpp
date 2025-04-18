/**
 * {SourceHeader}
 */

#pragma once

#include <string>

namespace Neon
{
    class IVertexBuffer;
    class BufferFactory
    {
        public:
            BufferFactory() = default;
            ~BufferFactory() = default;
        public:
            IVertexBuffer* CreateVertexBuffer(float* vertices, size_t size);
    };
}

