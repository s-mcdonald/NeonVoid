
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Runtime/Runtime.hpp>
#include <Runtime/Engine/Backends/Container.hpp>

#include "Input.hpp"

namespace Neon
{
    bool KeyboardInput::IsKeyPressed(Key key)
    {
        const auto& container = Container::GetInstance();
        auto& window = container.GetWindow();

        // @todo: refactor away from gl
        return glfwGetKey(&window, static_cast<int>(key)) == GLFW_PRESS;
    }

    bool KeyboardInput::IsKeyHeld(const Key key)
    {
        return KeyboardInput::IsKeyPressed(key);
    }

    bool KeyboardInput::IsKeyReleased(const Key key)
    {
        return false == KeyboardInput::IsKeyPressed(key);
    }
}
