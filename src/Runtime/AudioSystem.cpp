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
    AudioSystem::AudioSystem() : m_isPlaying(false)
    {
        ma_result result;
        ma_device_config deviceConfig = getDeviceConfig();
        result = ma_device_init(NULL, &deviceConfig, &m_device);

        if (result != MA_SUCCESS) 
        {
            std::cerr << "[ERROR] Failed to initialize audio device!" << std::endl;
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
            std::cerr << "[ERROR] Already playing audio!" << std::endl;
            return;
        }
    
        ma_result result = ma_decoder_init_file(filename.c_str(), NULL, &m_decoder);
        if (result != MA_SUCCESS) 
        {
            std::cerr << "[ERROR] Failed to load audio file: " << filename << std::endl;
            return;
        }
    
        result = ma_device_start(&m_device);
        if (result != MA_SUCCESS) 
        {
            std::cerr << "[ERROR] Failed to start playback!" << std::endl;
            return;
        }
    
        m_isPlaying = true;
        std::cout << "Playing audio: " << filename << std::endl;
    }

    void AudioSystem::Stop() 
    {
        if (!m_isPlaying) 
        {
            std::cerr << "[ERROR] No audio is playing!" << std::endl;
            return;
        }
    
        ma_device_stop(&m_device);
        m_isPlaying = false;

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

    void AudioSystem::dataCallback(ma_device* pDevice, void* pOutput, const void* pInput, uint32_t frameCount) {
        AudioSystem* player = reinterpret_cast<AudioSystem*>(pDevice->pUserData);

        if (player == nullptr) {
            std::cerr << "[ERROR] Player is null in callback!" << std::endl;
            return;
        }

        // Only enable in NEON_DEBUG_AUDIO mode
        //std::cout << "[DEBUG] Callback called with frameCount: " << frameCount << std::endl;

        // OK here is the guts of it, read from decoder into the OutputBuffer
        ma_decoder* pDecoder = &player->m_decoder;
        ma_result result = ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

        if (result != MA_SUCCESS) {
            std::cerr << "[ERROR] Failed to read PCM frames!" << std::endl;
            return;
        }
    }
}