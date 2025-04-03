/**
 * 
 */
#include <iostream>
#include <fstream>

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

    // Load SoundFiles

    // LoadTextures

    // ..
}
