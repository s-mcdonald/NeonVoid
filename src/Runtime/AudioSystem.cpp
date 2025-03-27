/**
 * 
 */
/* #define MINIAUDIO_IMPLEMENTATION */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>
#include "Runtime/Runtime.hpp"

namespace Neon 
{
    AudioSystem::AudioSystem() 
        : m_isPlaying(false)
        , m_onLoop(false)
    {
        ma_result result;
        ma_device_config deviceConfig = getDeviceConfig();
        result = ma_device_init(NULL, &deviceConfig, &m_device);

        if (result != MA_SUCCESS) 
        {
            #ifdef NEON_DEBUG_AUDIO
                std::cerr << "[ERROR] Failed to initialize audio device!" << std::endl;
            #endif
        }

        std::cout << "AudioSystem::Constructor completed\n";
    }

    AudioSystem::~AudioSystem() 
    {
        if (m_isPlaying) 
        {
            Stop();
        }

        ma_decoder_uninit(&m_decoder);
        ma_device_uninit(&m_device);

        std::cout << "AudioSystem::Destructor completed\n";
    }

    void AudioSystem::Play(const std::string& filename) 
    {
        if (m_isPlaying) 
        {
            #ifdef NEON_DEBUG_AUDIO
                std::cerr << "[ERROR] Already playing audio!" << std::endl;
            #endif

            return;
        }
    
        ma_result result = ma_decoder_init_file(filename.c_str(), NULL, &m_decoder);
        if (result != MA_SUCCESS) 
        {
            #ifdef NEON_DEBUG_AUDIO
                std::cerr << "[ERROR] Failed to load audio file: " << filename << std::endl;
            #endif
            
            return;
        }
    
        result = ma_device_start(&m_device);
        if (result != MA_SUCCESS) 
        {
            #ifdef NEON_DEBUG_AUDIO
                std::cerr << "[ERROR] Failed to start playback!" << std::endl;
            #endif
            
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
        if (!m_isPlaying) 
        {
            #ifdef NEON_DEBUG_AUDIO
                std::cerr << "[ERROR] No audio is playing!" << std::endl;
            #endif
            
            return;
        }
    
        ma_device_stop(&m_device);
        m_isPlaying = false;

        ma_decoder_seek_to_pcm_frame(&m_decoder, 0);

        std::cout << "Audio stopped!" << std::endl;
    }

    ma_device_config AudioSystem::getDeviceConfig() 
    {
        ma_device_config config = ma_device_config_init(ma_device_type_playback);
    
        config.playback.format   = ma_format_f32;
        config.playback.channels = 2;
        config.sampleRate        = 44100;
        config.dataCallback      = AudioSystem::dataCallback;
        config.pUserData        = this;
    
    
        return config;
    }

    void AudioSystem::dataCallback(ma_device* pDevice, void* pOutput, const void* pInput, uint32_t frameCount) 
    {
        AudioSystem* player = reinterpret_cast<AudioSystem*>(pDevice->pUserData);

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
        ma_result result = ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

        switch(result)
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
}