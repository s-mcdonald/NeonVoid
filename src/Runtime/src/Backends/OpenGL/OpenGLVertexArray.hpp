/**
 * {SourceHeader}
 */

#pragma once

#include <Backends/IVertexArray.hpp>

namespace Neon
{
    class OpenGLVertexArray : public IVertexArray
    {
        virtual void Bind() const override;
        virtual void Unbind() const override;
    };
}

