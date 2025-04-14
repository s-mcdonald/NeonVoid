/**
 * {SourceHeader}
 */

#include <NeonEngine/Runtime.hpp>
#include <Runtime/Container.hpp>

#include <Runtime/Backends/OpenGL/OpenGLHeaders.hpp>
#include <Runtime/Backends/OpenGL/OpenGLInput.hpp>

namespace Neon
{
    bool OpenGLKeyboardInput::IsKeyPressed(Key key)
    {
        const auto& container = Container::GetInstance();
        GLFWwindow& window = *static_cast<GLFWwindow*>(container.GetWindowAsPtr());
        return glfwGetKey(&window, static_cast<int>(key)) == GLFW_PRESS;
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
