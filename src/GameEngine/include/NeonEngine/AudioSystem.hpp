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

#pragma once

#include <string>

#include <miniaudio/miniaudio.h>

#include <NeonEngine/Volume.hpp>

namespace Neon 
{
    class AudioSystem
    {
        public:
            AudioSystem();
            virtual ~AudioSystem();

            virtual void Play(const std::string& filename);
            virtual void PlayOnce(const std::string& filename);
            virtual void PlayOnLoop(const std::string& filename);
            virtual void Stop();
            virtual void Update();
            void ResetDecoder();

            virtual void SetVolume(const Volume& volume);

        private:
            ma_device_config getDeviceConfig();
            static void dataCallback(ma_device* pDevice, void* pOutput, const void* pInput, uint32_t frameCount);

        private:
            ma_context m_context{};
            ma_decoder m_decoder{};
            ma_device m_device{};
            bool m_isPlaying{false};
            bool m_onLoop{false};
            bool m_isStopRequested{false};
            bool m_isAudioEnabled{false};
    };
}
