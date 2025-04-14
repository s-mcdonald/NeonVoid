/**
 * {SourceHeader}
 */

#pragma once

#include <NeonEngine/Types.hpp>

namespace Neon
{
    class Shader
    {
        public:
            Shader() = default;
            virtual ~Shader() = default;

        public:
            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;

        public:
            virtual void OnInit() = 0;
            virtual void OnDelete() = 0;
            [[nodiscard]] virtual uint32_t GetShaderProgramId() const = 0;
    };
}
