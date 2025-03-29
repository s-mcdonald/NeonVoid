/**
 *
 */

#pragma once

#include <iostream>
#include <stdexcept>
#include <cstdint>

namespace Neon 
{
    class Volume
    {
        public:
            Volume(uint8_t volume) : m_volume(volume) 
            {
               //static_assert(volume <= 100, "Volume must be between 0 and 100");
            }
        
            uint8_t GetVolume() const 
            {
                return m_volume;
            }

        private:
            uint8_t m_volume;
    };
}