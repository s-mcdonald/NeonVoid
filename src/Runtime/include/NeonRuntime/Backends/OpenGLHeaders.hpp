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

#include <string>

#include "glad/glad.h"   // Include glad first
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

// move to a custom types file later
struct DrawTextMeta
{
    // position
    float x = 25.0f;
    float y = 100.0f;

    // size
    float scale = 0.5f;

    // text
    std::string text = "";

    // RGB color struct
    struct
    {
        float r = 1.0f;
        float g = 0.0f;
        float b = 0.0f;
    } rgb;

    struct
    {
        float top = 900.0f;
        float right = 1000.0f;
    } orthoProjection;
};
