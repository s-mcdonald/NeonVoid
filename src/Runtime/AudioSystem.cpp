/**
 * 
 */
#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For usleep (sleep in milliseconds)

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    AudioSystem::AudioSystem()
    {
        //
    }

    AudioSystem::~AudioSystem() 
    {
        //
    }
}