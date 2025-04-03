/**
*
*/
#include "OpenGLVertexBuffer.hpp"

namespace Neon
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, size_t size)
    {
        // Generate m_VAO and m_VBO
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        // Bind m_VAO and m_VBO
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

        // Set the vertex attribute pointer
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // Unbind m_VBO and m_VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        if (m_VAO)
        {
            glDeleteVertexArrays(1, &m_VAO);
            m_VAO = 0;
        }

        if (m_VBO)
        {
            glDeleteBuffers(1, &m_VBO);
            m_VBO = 0;
        }
    }

    GLuint OpenGLVertexBuffer::GetVao()
    {
        return m_VAO;
    }

    void OpenGLVertexBuffer::Bind() const
    {
        //
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        //
    }

    void OpenGLVertexBuffer::UpdateData(const void* data, size_t size)
    {
        //
    }
}