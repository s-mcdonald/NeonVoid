
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Runtime/Runtime.hpp>
#include <Runtime/Runtime/Container.hpp>

#include <Runtime/Runtime/Backends/OpenGL/OpenGLInput.hpp>

namespace Neon
{
    bool OpenGLKeyboardInput::IsKeyPressed(Key key)
    {
        const auto& container = Container::GetInstance();
        auto& window = container.GetWindow();

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
