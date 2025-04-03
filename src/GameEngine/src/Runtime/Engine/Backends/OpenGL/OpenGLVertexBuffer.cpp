/**
*
*/
#include "OpenGLVertexBuffer.hpp"

namespace Neon
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, size_t size)
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_VBO);
        glDeleteVertexArrays(1, &m_VAO);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindVertexArray(m_VAO);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexBuffer::UpdateData(const void* data, size_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }
}