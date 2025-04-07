/**
 * 
 */
#include <fstream>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Runtime/Runtime.hpp>

namespace Neon 
{
    void OpenGLRenderer::BeginFrame()
    {
        glClearColor(0.0f,0.0f,0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void OpenGLRenderer::EndFrame()
    {
        glFlush();
    }

    void OpenGLRenderer::RenderText(const TextComponent& component)
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "OpenGLRenderer::RenderText called\n";
        #endif

        std::cout << "Rendering Text: " << component.GetText() << std::endl;
    }

    void OpenGLRenderer::RenderQuad(const GLuint shaderProgram, const GLuint VAO)
    {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glBindVertexArray(0);
    }

    void OpenGLRenderer::RenderCircle(const GLuint shaderProgram, const GLuint VAO, const GLsizei vertexCount)
    {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
        glBindVertexArray(0);
    }
}
