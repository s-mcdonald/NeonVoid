/**
 * 
 */
#include <iostream>
#include <cmath>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    AudioComponent::AudioComponent()
    {
        std::cout << "AudioComponent::Constructor called\n";
    }

    AudioComponent::~AudioComponent() 
    {
        std::cout << "AudioComponent::Destructor completed\n";
    }

    void AudioComponent::OnInit() 
    {
        //
    }

    void AudioComponent::OnUpdate() 
    {
        //
    }
}
