/**
 *
 */

#pragma once

#include <cstdint>

namespace Neon 
{
   // typedef float Volume;

   struct AudioConfig {
      bool repeat = false;
      bool onInit = false;
      // void* onAction;
      // void* onEvent;
   };

   typedef struct {
      uint16_t x;
      uint16_t y;
  } Point;
}

