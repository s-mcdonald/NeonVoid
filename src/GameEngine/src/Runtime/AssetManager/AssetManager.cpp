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
    AssetManager::AssetManager()
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "AssetManager::Constructor called\n";
        #endif
    }

    AssetManager::~AssetManager() 
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "AssetManager::~Destructor called\n";
        #endif

        delete m_fontBuffer;
    }

    bool AssetManager::LoadTrueTypeFont(const char* fontPath)
    {
        std::ifstream fontFile(fontPath, std::ios::binary);
        std::vector<unsigned char> fontData((std::istreambuf_iterator<char>(fontFile)), std::istreambuf_iterator<char>());
        m_fontBuffer = fontData.data();

        if (!stbtt_InitFont(&m_font, m_fontBuffer, 0)) 
        {
            std::cerr << "Failed to initialize font." << std::endl;

            return false;
        }

        return true;
    }
}
