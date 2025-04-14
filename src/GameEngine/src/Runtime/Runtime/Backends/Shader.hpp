/**
 * {SourceHeader}
 */

#pragma once

#include <Runtime/Types.hpp>

namespace Neon
{
    class Shader
    {
        public:
            Shader() = default;
            virtual ~Shader() = default;

        public:
            virtual void OnInit() = 0;
            virtual void OnDelete() = 0;
            [[nodiscard]] virtual uint32_t GetShaderProgramId() const = 0;
    };
}
