/**
 * {SourceHeader}
 */

#pragma once

namespace Neon
{
    class IVertexArray
    {
        public:
            virtual ~IVertexArray() = default;

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;
    };
}
