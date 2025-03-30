/**
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_TRUETYPE_IMPLEMENTATION


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

        delete m_fontBuffer;
    }

    /// @brief Load font into memory
    void OpenGLRenderer::LoadFont(const char* fontPath)
    {
        std::ifstream fontFile(fontPath, std::ios::binary);
        std::vector<unsigned char> fontData((std::istreambuf_iterator<char>(fontFile)), std::istreambuf_iterator<char>());
        m_fontBuffer = fontData.data();

        if (!stbtt_InitFont(&m_font, m_fontBuffer, 0)) 
        {
            std::cerr << "Failed to initialize font." << std::endl;
        }
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
        for (size_t i = 0; i < text.length(); ++i)
        {

        }
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

    GLuint OpenGLRenderer::createTextureFromBitmap(unsigned char* bitmap, int width, int height) 
    {
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
    
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        return textureID;
    }
}
