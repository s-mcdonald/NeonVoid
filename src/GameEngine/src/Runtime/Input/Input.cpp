
#include "Input.hpp"

namespace Neon
{
    bool KeyboardInput::IsKeyPressed(Key key) const
    {
        return false;
    }

    bool KeyboardInput::IsKeyHeld(Key key) const
    {
        return false;
    }

    bool KeyboardInput::IsKeyReleased(Key key) const
    {
        return false;
    }

    int MouseInput::GetMouseX() const
    {
        return 0;
    }

    int MouseInput::GetMouseY() const
    {
        return 0;
    }

//    bool MouseInput::IsMouseButtonPressed(MouseButton button) const
//    {
//        return true;
//    }
}