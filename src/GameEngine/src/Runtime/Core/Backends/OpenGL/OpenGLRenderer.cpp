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

    void OpenGLRenderer::RenderText([[ maybe_unused ]] const TextComponent& component)
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "OpenGLRenderer::RenderText called\n";
        #endif

        // component.GetPosition().X, component->GetPosition().Y
        RenderText(component.GetText(), 0, 0, 18);
    }

    void OpenGLRenderer::RenderText(const std::string& text, float x, float y, int fontSize) 
    {
        std::cout << "Renderring Text: " << text << std::endl;
    }

    [[ maybe_unused ]] void OpenGLRenderer::RenderTriangle(
        [[ maybe_unused ]] float x1, 
        [[ maybe_unused ]] float y1, 
        [[ maybe_unused ]] float x2, 
        [[ maybe_unused ]] float y2, 
        [[ maybe_unused ]] float x3, 
        [[ maybe_unused ]] float y3, 
        [[ maybe_unused ]] const Color& color
    )
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "OpenGLRenderer::RenderTriangle called\n";
        #endif
    }
}
