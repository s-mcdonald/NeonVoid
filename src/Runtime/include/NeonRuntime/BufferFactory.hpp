/**
 * {SourceHeader}
 */

#pragma once

#include <stddef.h>

namespace Neon
{
    class IVertexBuffer;
    class BufferFactory
    {
        public:
            BufferFactory() = default;
            ~BufferFactory() = default;

            IVertexBuffer* CreateVertexBuffer(float* vertices, size_t size);
    };
}
