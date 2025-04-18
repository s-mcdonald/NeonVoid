/**
 * {SourceHeader}
 */

#pragma once

#include <NeonRuntime/Backends/OpenGLHeaders.hpp>
#include <NeonRuntime/IVertexArray.hpp>

namespace Neon
{
    class OpenGLVertexArray : public IVertexArray
    {
        public:
            OpenGLVertexArray();
            ~OpenGLVertexArray() override;

            void Bind() const override;
            void Unbind() const override;

        private:
            GLuint m_vaoId{0};
    };
}

