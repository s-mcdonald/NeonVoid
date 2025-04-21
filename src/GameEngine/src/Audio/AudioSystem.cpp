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
#include <string>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio/miniaudio.h>

#include <NeonEngine/AudioSystem.hpp>

namespace Neon 
{
    AudioSystem::AudioSystem()
    {
        const ma_device_config deviceConfig = getDeviceConfig();

        if (const ma_result result = ma_device_init(nullptr, &deviceConfig, &m_device); result != MA_SUCCESS)
        {
            m_isAudioEnabled = false;
        }
        else
        {
            m_isAudioEnabled = true;
        }
    }

    AudioSystem::~AudioSystem() 
    {
        if (true == m_isPlaying)
        {
            Stop();
        }

        if (m_isAudioEnabled)
        {
            ma_device_uninit(&m_device);
        }

        ma_decoder_seek_to_pcm_frame(&m_decoder, 0);
        ma_decoder_uninit(&m_decoder);
    }

    void AudioSystem::Play(const std::string& filename) 
    {
        if (true == m_isPlaying && true == m_isAudioEnabled)
        {
            return;
        }

        if (m_isPlaying)
        {
            ma_decoder_uninit(&m_decoder);
        }

        ma_result result = ma_decoder_init_file(filename.c_str(), nullptr, &m_decoder);
        if (result != MA_SUCCESS) 
        {
            return;
        }
    
        result = ma_device_start(&m_device);
        if (result != MA_SUCCESS) 
        {
            return;
        }
    
        m_isPlaying = true;
    }

    void AudioSystem::PlayOnce(const std::string& filename)
    {
        m_onLoop = false;
        Play(filename);
    }

    void AudioSystem::PlayOnLoop(const std::string& filename)
    {
        m_onLoop = true;
        Play(filename);
    }

    void AudioSystem::Stop() 
    {
        if (false == m_isPlaying)
        {
            return;
        }
    
        ma_device_stop(&m_device);
        ma_decoder_uninit(&m_decoder);
        m_isPlaying = false;

        ma_decoder_seek_to_pcm_frame(&m_decoder, 0);

#if defined(NEON_DEBUG) && defined(NEON_DEBUG_AUDIO)
        std::cout << "Audio stopped!" << std::endl;
#endif
    }

    void AudioSystem::Update() 
    {
        if (m_isStopRequested) 
        {
#ifdef NEON_DEBUG_AUDIO
            std::cerr << "[INFO] Attempting to stop player." << std::endl;
#endif
            
            Stop();
            m_isStopRequested = false;
        }
    }

    void AudioSystem::SetVolume([[ maybe_unused ]]const Volume& volume) 
    {
#ifdef NEON_DEBUG_AUDIO
        std::cerr << "[INFO] Set volume..." << std::endl;
#endif

        float normalizedVolume = static_cast<float>(volume.GetVolume()) / 100.0f;
        ma_device_set_master_volume(&m_device, normalizedVolume);
    }

    ma_device_config AudioSystem::getDeviceConfig() 
    {
        ma_device_config config = ma_device_config_init(ma_device_type_playback);
    
        config.playback.format      = ma_format_f32;
        config.playback.channels    = 2;
        config.sampleRate           = 44100;
        config.dataCallback         = AudioSystem::dataCallback;
        config.pUserData            = this;
    
        return config;
    }

    // We may want to change volume at some point
    // void AudioSystem::SetVolume(Volume v)
    // {
    //     auto x* = ma_device_get_master_volume(m_device);
    //     ma_device_set_master_volume_db(ma_device* pDevice, float gainDB)
    // }

    void AudioSystem::dataCallback(ma_device* pDevice, void* pOutput, [[maybe_unused]] const void* pInput, uint32_t frameCount) 
    {
        auto* player = static_cast<AudioSystem*>(pDevice->pUserData);

        if (player == nullptr) 
        {
#ifdef NEON_DEBUG_AUDIO
            std::cerr << "[ERROR] Player is null in callback!" << std::endl;
#endif
            
            return;
        }

#ifdef NEON_DEBUG_AUDIO
        std::cout << "[DEBUG] Callback called with frameCount: " << frameCount << std::endl;
#endif

        // OK here is the guts of it, read from decoder into the OutputBuffer
        ma_decoder* pDecoder = &player->m_decoder;

        switch(ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, nullptr))
        {
            case MA_AT_END:
                if (false == player->m_onLoop) 
                {
#ifdef NEON_DEBUG_AUDIO
                    std::cout << "[INFO] Reached end of file, stopping audio." << std::endl;
#endif
        
                    player->m_isStopRequested = true;
                    return;
                } 

#ifdef NEON_DEBUG_AUDIO
                std::cout << "[INFO] Reached end of file, replay because on loop." << std::endl;
#endif

                ma_decoder_seek_to_pcm_frame(pDecoder, 0);
                break;
            case MA_SUCCESS:
                break;
            default:
#ifdef NEON_DEBUG_AUDIO
                std::cerr << "[ERROR] Failed to read PCM frames!" << std::endl;
#endif
                break;
        }
    }
}