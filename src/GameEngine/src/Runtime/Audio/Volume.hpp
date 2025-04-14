/**
 * {SourceHeader}
 */

#pragma once

#include <cstdint>
#include <iostream>
#include <stdexcept>

namespace Neon 
{
    class Volume
    {
        public:
            explicit Volume(const uint8_t volume) : m_volume(volume)
            {
               //static_assert(volume <= 100, "Volume must be between 0 and 100");
            }
        
            [[nodiscard]] uint8_t GetVolume() const
            {
                return m_volume;
            }

        private:
            uint8_t m_volume;
    };
}