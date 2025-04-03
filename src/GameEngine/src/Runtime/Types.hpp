/**
 *
 */

#pragma once

#include <cstdint>

namespace Neon 
{
   constexpr float MIN_FONT_SIZE = 8;
   constexpr float BASE_FONT_SIZE = 18;
   constexpr float MULTIPLIER_RESOLUTION = 1;

   constexpr float NV_DEFAULT_FONT_SIZE = BASE_FONT_SIZE * MULTIPLIER_RESOLUTION;
   constexpr float NV_MINIMUM_FONT_SIZE = MIN_FONT_SIZE * MULTIPLIER_RESOLUTION;

   typedef struct
   {
      float x, y;
   } Vec2;

   typedef struct
   {
      float x, y, z;
   } Vec3;

   typedef struct
   {
      float r, g, b;
   } Color;

   typedef struct
   {
      float r, g, b, a;
   } ColorAlpha;

   typedef struct  
   {
      bool repeat = false;
      uint8_t delay = 0; // milliseconds of delay time once play initialized
   } AudioConfig;

   struct Point
   {
      int16_t x;
      int16_t y;
   };

   enum class SceneType
   {
      Title = 0,
      Menu,
      Gameplay,
      Pause
   };
}

