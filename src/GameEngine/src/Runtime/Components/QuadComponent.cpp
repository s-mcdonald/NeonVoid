/**
 * 
 */
#include <iostream>
#include <cmath>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    QuadComponent::QuadComponent() 
        : Component()
        , m_VAO(0)
        , m_VBO(0)
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "QuadComponent::Constructor called\n";
        #endif
    }

    // @todo: Abstract this to platforms
    QuadComponent::~QuadComponent() 
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

        if (m_shaderProgram) 
        {
            glDeleteProgram(m_shaderProgram);
            m_shaderProgram = 0;
        }

        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "QuadComponent::Destructor completed\n";
        #endif
    }

    void QuadComponent::OnInit() 
    {
        GLfloat vertices[] = {
            0.0f,  0.5f,        // Top vertex
            -0.5f, -0.5f,       // Bottom left
            0.5f, -0.5f,        // Bottom right
        };

        // Generate m_VAO and m_VBO
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        // Bind m_VAO and m_VBO
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Set the vertex attribute pointer
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // Unbind m_VBO and m_VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Compile and link shaders
        const char* vertexSource = R"(
            #version 330 core
            layout(location = 0) in vec2 position;
            void main() {
                gl_Position = vec4(position, 0.0f, 1.0f);
            })";

        const char* fragmentSource = R"(
            #version 330 core
            out vec4 FragColor;
            void main() {
                FragColor = vec4(0.4f, 0.7f, 0.2f, 1.0f);
            })";

        m_shaderProgram = OpenGL::CreateShaderProgram(vertexSource, fragmentSource);
    }

    void QuadComponent::OnUpdate() 
    {
        auto& api = GameEngineApi::getInstance();
        api.GetRenderer()->RenderQuad(m_shaderProgram, m_VAO);
    }
}
