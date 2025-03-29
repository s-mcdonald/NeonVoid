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
   } AudioConfig;

   typedef struct 
   {
      uint16_t x;
      uint16_t y;
   } Point;
}

