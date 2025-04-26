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
        : m_decoder{}
        , m_device{}
    {
        const ma_device_config deviceConfig = getDeviceConfig();

        if (const ma_result result = ma_device_init(nullptr, &deviceConfig, &m_device); result != MA_SUCCESS)
        {
            m_isAudioEnabled = false;
        }
        else
        {

            if (ma_context_init(nullptr, 0, nullptr, &m_context) != MA_SUCCESS)
            {
                m_isAudioEnabled = false;
            }
            else
            {
                m_isAudioEnabled = true;
            }
        }
    }

    AudioSystem::~AudioSystem() 
    {
        if (m_isPlaying)
        {
            Stop();
        }

        ma_device_uninit(&m_device);
        ma_decoder_uninit(&m_decoder);

        ResetDecoder();
        ma_context_uninit(&m_context);
    }

    void AudioSystem::Play(const std::string& filename) 
    {
        if (m_isPlaying)
        {
            Stop();
        }

        ma_result result = ma_decoder_init_file(filename.c_str(), nullptr, &m_decoder);
        if (result != MA_SUCCESS)
        {
            m_isPlaying = false;
            return;
        }

        result = ma_device_start(&m_device);
        if (result != MA_SUCCESS)
        {
            ma_decoder_uninit(&m_decoder);
            m_isPlaying = false;
            return;
        }

        m_isPlaying = true;
    }

    void AudioSystem::PlayOnce(const std::string& filename)
    {
        ResetDecoder();
        m_onLoop = false;
        Play(filename);
    }

    void AudioSystem::PlayOnLoop(const std::string& filename)
    {
        ResetDecoder();
        m_onLoop = true;
        Play(filename);
    }

    void AudioSystem::Stop() 
    {
        if (!m_isPlaying)
        {
            return;
        }

        ma_device_stop(&m_device);

        if (m_decoder.outputFormat != ma_format_unknown) {
            ma_decoder_uninit(&m_decoder);
            m_decoder = {};
        }

        m_decoder = {};
        m_isPlaying = false;
        m_isStopRequested = false;
    }

    void AudioSystem::Update() 
    {
        if (m_isStopRequested)
        {
            Stop();
        }
    }

    void AudioSystem::SetVolume([[ maybe_unused ]]const Volume& volume) 
    {
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

    void AudioSystem::ResetDecoder()
    {
        if (m_decoder.outputFormat != ma_format_unknown)
        {
            ma_decoder_seek_to_pcm_frame(&m_decoder, 0);
            ma_decoder_uninit(&m_decoder);
            m_decoder = {};
        }
    }

    void AudioSystem::dataCallback(ma_device* pDevice, void* pOutput, [[maybe_unused]] const void* pInput, uint32_t frameCount)
    {
        auto* player = static_cast<AudioSystem*>(pDevice->pUserData);

        if (!player || !player->m_isPlaying)
        {
            return;
        }

        ma_decoder* pDecoder = &player->m_decoder;

        ma_result result = ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, nullptr);
        if (result == MA_AT_END)
        {
            if (!player->m_onLoop)
            {
                player->m_isStopRequested = true;
            }
            else
            {
                ma_decoder_seek_to_pcm_frame(pDecoder, 0);
                ma_decoder_uninit(pDecoder);
            }
        }
        else if (result != MA_SUCCESS)
        {
            player->m_isStopRequested = true;
        }
    }
}