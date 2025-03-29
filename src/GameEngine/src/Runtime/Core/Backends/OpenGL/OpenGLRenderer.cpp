/**
 * 
 */
#include <iostream>

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

    void OpenGLRenderer::RenderText(const TextComponent& component)
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "OpenGLRenderer::RenderText called\n";
        #endif
    }

    void OpenGLRenderer::RenderTriangle(float x1, float y1, float x2, float y2, float x3, float y3, const Color& color)
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "OpenGLRenderer::RenderTriangle called\n";
        #endif
    }
}
