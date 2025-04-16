/**
 * {SourceHeader}
 */

#pragma once

#include <cstdint>                          // For uint32_t

namespace Neon
{
    class IShader
    {
        public:
            IShader() = default;
            virtual ~IShader() = default;

        public:
            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;

        public:
            virtual void OnInit() = 0;
            virtual void OnDelete() = 0;
            [[nodiscard]] virtual uint32_t GetShaderProgramId() const = 0;
    };
}
