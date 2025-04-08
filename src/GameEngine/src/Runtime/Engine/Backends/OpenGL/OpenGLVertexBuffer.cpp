
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Runtime/Engine/Backends/OpenGL/OpenGLVertexBuffer.hpp>

namespace Neon
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, const size_t size)
        : m_vertices(vertices), m_size(size)
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
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

    uint32_t OpenGLVertexBuffer::GetVao()
    {
        return m_VAO;
    }

    uint32_t OpenGLVertexBuffer::GetVbo()
    {
        return m_VBO;
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, static_cast<short>(m_size), m_vertices, GL_STATIC_DRAW);

        // Set the vertex attribute pointer
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void OpenGLVertexBuffer::UpdateData(const void* data, size_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, GetVbo());
        glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<short>(size), data);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}