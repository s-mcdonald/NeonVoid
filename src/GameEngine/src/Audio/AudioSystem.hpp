/**
 * {SourceHeader}
 */

#pragma once

#include <miniaudio/miniaudio.h>
#include <string>

#include "Volume.hpp"

namespace Neon 
{
    class AudioSystem 
    {
        public:
            AudioSystem();
            virtual ~AudioSystem();

        public:
            virtual void Play(const std::string& filename);
            virtual void PlayOnce(const std::string& filename);
            virtual void PlayOnLoop(const std::string& filename);
            virtual void Stop();
            virtual void Update();

            virtual void SetVolume(const Volume& volume);

        private:
            ma_device_config getDeviceConfig();
            static void dataCallback(ma_device* pDevice, void* pOutput, const void* pInput, uint32_t frameCount);

        private:
            ma_decoder m_decoder{};
            ma_device m_device{};
            bool m_isPlaying{false};
            bool m_onLoop{false};
            bool m_isStopRequested{false};
            bool m_isAudioEnabled{false};
    };
}