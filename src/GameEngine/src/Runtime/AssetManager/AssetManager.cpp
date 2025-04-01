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
    }

    // bool AssetManager::LoadTrueTypeFont(const char* fontPath)
    // {
    //     return true;
    // }
}
