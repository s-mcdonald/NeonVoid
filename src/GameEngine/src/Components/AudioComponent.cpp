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

#include <NeonEngine/Components.hpp>

namespace Neon
{
    AudioComponent::~AudioComponent()
    {
        AudioSystem::Stop();
        AudioSystem::~AudioSystem();
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
        m_volume.SetVolume(volume);
        AudioSystem::SetVolume(volume);
    }

    void AudioComponent::OnDestroy()
    {
        // ....
    }
}
