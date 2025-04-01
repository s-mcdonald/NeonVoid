/**
 * 
 */
#include <iostream>
#include <cmath>
#include <utility>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    // AudioConfig config
    AudioComponent::AudioComponent(std::string filename)
        : Component()
        , AudioSystem()
        , m_filename(std::move(filename))
        , m_repeats(false)
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "AudioComponent::Constructor called\n";
        #endif
    }

    AudioComponent::~AudioComponent() 
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "AudioComponent::Destructor completed\n";
        #endif
    }

    ///
    /// @brief change so that we can pass config to how/when to play.
    ///
    void AudioComponent::OnInit() 
    {
        //
    }

    void AudioComponent::OnUpdate() 
    {
        //
    }

    void AudioComponent::TriggerPlayOnce() 
    {
        PlayOnce(m_filename);
    }

    void AudioComponent::TriggerPlayRepeat() 
    {
        PlayOnLoop(m_filename);
    }

    void AudioComponent::SetVolume(const Volume& volume) 
    {
        AudioSystem::SetVolume(volume);
    }
}
