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
#include <NeonRuntime/Backends/OpenGLInput.hpp>

namespace Neon
{
    bool OpenGLKeyboardInput::IsKeyPressed(Key key)
    {
        return glfwGetKey(mx_window, static_cast<int>(key)) == GLFW_PRESS;
    }

    bool OpenGLKeyboardInput::IsKeyHeld(const Key key)
    {
        return OpenGLKeyboardInput::IsKeyPressed(key);
    }

    bool OpenGLKeyboardInput::IsKeyReleased(const Key key)
    {
        return false == OpenGLKeyboardInput::IsKeyPressed(key);
    }
}
