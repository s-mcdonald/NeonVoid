/**
 * {SourceHeader}
 */

#pragma once

#include <cstdint>

namespace Neon
{
    class IVertexBuffer
    {
        public:
            virtual ~IVertexBuffer() = default;

        public:
            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;
            virtual void UpdateData(const void* data, size_t size) = 0;

            virtual uint32_t GetVao() = 0;
            virtual uint32_t GetVbo() = 0;
    };
}
