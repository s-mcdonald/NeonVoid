/**
 * {SourceHeader}
 */

#pragma once

namespace Neon
{
    class IFrameBuffer
    {
        public:
            virtual ~IFrameBuffer() = default;

            void Invalidate();

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;
    };
}
