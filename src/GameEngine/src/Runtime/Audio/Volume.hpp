/**
 *
 */

#pragma once

#include <iostream>
#include <cstdint>

namespace Neon 
{
    class Volume
    {
        public:
            constexpr Volume(const uint8_t volume) : m_volume(volume) 
            {
                static_assert(volume >= 0 && volume <= 100, "Volume must be between 0 and 100");
            }
        
            int GetVolume() const 
            {
                return m_volume;
            }

        private:
            uint8_t m_volume;
    };
}