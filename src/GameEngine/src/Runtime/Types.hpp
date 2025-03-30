/**
 *
 */

#pragma once

#include <cstdint>

namespace Neon 
{
   typedef struct
   {
      float x, y, z;
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

