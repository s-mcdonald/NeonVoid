/**
 *
 */

#pragma once

#include <cstdint>

namespace Neon 
{
   typedef struct
   {
      float x, y, z, w;
   } Vec4;

   typedef Vec4 Color;

   typedef struct  
   {
      bool repeat = false;
      uint8_t delay = 0; // milliseconds of delay time once play initialized
   } AudioConfig;

   struct Point
   {
      uint16_t x;
      uint16_t y;
   };

   enum class SceneType
   {
      Title = 0,
      Menu,
      Gameplay,
      Pause
   };
}

