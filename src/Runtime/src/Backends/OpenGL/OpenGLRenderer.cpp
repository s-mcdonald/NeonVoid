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

#include <fstream>
#include <iostream>
#include <map>

#include <NeonRuntime/Backends/OpenGLHeaders.hpp>
#include <NeonRuntime/Backends/OpenGLRenderer.hpp>

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

    void OpenGLRenderer::RenderTriangle(const GLuint shaderProgram, const GLuint VAO, const GLsizei vertexCount)
    {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        glBindVertexArray(0);
    }

    void OpenGLRenderer::RenderText(const GLuint shaderProgram, const GLuint VAO, const std::string& text)
    {
        // ..
        std::cout << "Rendering Text: " << text << std::endl;
    }
}
