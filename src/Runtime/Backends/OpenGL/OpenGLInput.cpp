/**
 * {SourceHeader}
 */

#include <Runtime/Backends/OpenGL/OpenGLInput.hpp>

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
