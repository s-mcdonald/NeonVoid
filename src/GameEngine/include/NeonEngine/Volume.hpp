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

#include <cstdint>

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

            void SetVolume(Volume v)
            {
                m_volume = v.GetVolume();
            }

        private:
            uint8_t m_volume;
    };
}