/**
 * {SourceHeader}
 */

#include <NeonRuntime/Backends/OpenGLVertexArray.hpp>

namespace Neon
{
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_vaoId);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_vaoId);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_vaoId);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }
}
