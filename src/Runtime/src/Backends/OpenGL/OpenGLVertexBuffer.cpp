/**
 *    ███╗   ██╗███████╗ ██████╗ ███╗   ██╗
 *    ████╗  ██║██╔════╝██╔═══██╗████╗  ██║
 *    ██╔██╗ ██║█████╗  ██║   ██║██╔██╗ ██║
 *    ██║╚██╗██║██╔══╝  ██║   ██║██║╚██╗██║
 *    ██║ ╚████║███████╗╚██████╔╝██║ ╚████║
 *    ╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═══╝
 * ========================================
 *                 NeonVoid
 *         A 2D Game Engine in C++
 * ----------------------------------------
 * License: MIT
 * Copyright (c) : 2024 Sam McDonald
 * Repository: https://github.com/s-mcdonald/NeonVoid
 */

#include <NeonRuntime/Backends/OpenGLHeaders.hpp>
#include <NeonRuntime/Backends/OpenGLVertexBuffer.hpp>

namespace Neon
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, const int* indices, const size_t size)
        : m_vertices(vertices)
        , m_indices(indices)
        , m_size(size)
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);
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

        if (m_EBO)
        {
            glDeleteBuffers(1, &m_EBO);
            m_EBO = 0;
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
        glBufferData(GL_ARRAY_BUFFER, m_size, m_vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void OpenGLVertexBuffer::UpdateData(const void* data, size_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, GetVbo());
        glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(size), data);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::UpdateIndices(const void* indices, size_t size)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(size), indices);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
