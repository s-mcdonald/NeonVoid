/**
 * 
 */
#include <iostream>
#include <cmath>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    Scene::Scene(Platform* platform) 
        : IRenderable()
        , m_platform(platform)
        , VAO(0)
        , VBO(0)
    {
        std::cout << "Scene::Constructor called\n";
    }

    Scene::~Scene() 
    {
        std::cout << "Scene::Destructor called\n";
        if (VAO) glDeleteVertexArrays(1, &VAO);
        if (VBO) glDeleteBuffers(1, &VBO);
        if (shaderProgram) glDeleteProgram(shaderProgram);  // Delete shader program
    }

    void Scene::Init()
    {
        std::cout << "Scene::Init() [IRenderable]\n";

        // Define a simple triangle
        GLfloat vertices[] = {
            0.0f,  0.5f,    // Top vertex
            -0.5f, -0.5f,   // Bottom left
            0.5f, -0.5f     // Bottom right
        };
    
        // Generate VAO and VBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
    
        // Bind VAO and VBO
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
        // Set the vertex attribute pointer
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
    
        // Unbind VBO and VAO
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
    
        shaderProgram = m_platform->createShaderProgram(vertexSource, fragmentSource);
    
        std::cout << "Scene::Init() [Complete]\n";
    }

    void Scene::Render()
    {       
        std::cout << "Scene::Rendering..\n";

        glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
    
        glUseProgram(shaderProgram);  // Use the shader program
    
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    
        m_platform->TriggerPostRedisplay();
    }
}
