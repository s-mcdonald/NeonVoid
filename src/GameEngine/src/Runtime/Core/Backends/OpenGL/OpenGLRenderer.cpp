/**
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    OpenGLRenderer::OpenGLRenderer()
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "OpenGLRenderer::Constructor called\n";
        #endif
    }

    OpenGLRenderer::~OpenGLRenderer() 
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "OpenGLRenderer::~Destructor called\n";
        #endif
    }

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

    void OpenGLRenderer::RenderQuad(GLuint shaderProgram, GLuint VAO) 
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "OpenGLRenderer::RenderQuad called\n";
        #endif

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
    
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glBindVertexArray(0);
    }
}
