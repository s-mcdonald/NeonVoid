/**
 * 
 */
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    GLuint GlComponentInitializer::InitQuadComponent(QuadComponent* component)
    {
        const auto vertices = static_cast<GLfloat>(component->GetVerticies());

        GLuint m_VAO;
        GLuint m_VBO;

        // Generate m_VAO and m_VBO
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        // Bind m_VAO and m_VBO
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        // Set the vertex attribute pointer
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // Unbind m_VBO and m_VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return m_VAO;
    }
}
