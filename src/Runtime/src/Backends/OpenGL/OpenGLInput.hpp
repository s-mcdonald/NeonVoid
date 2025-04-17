/**
 * {SourceHeader}
 */

#pragma once

#include <Backends/IInput.hpp>

namespace Neon
{
    class OpenGLKeyboardInput : public KeyboardInput
    {
        public:
            explicit OpenGLKeyboardInput(GLFWwindow* window)
                : KeyboardInput(window)
                , mx_window(window)
                {
                    //
                };
            ~OpenGLKeyboardInput() override = default;

        public:
            [[nodiscard]] bool IsKeyPressed(Key key) override;
            [[nodiscard]] bool IsKeyHeld(Key key) override;
            [[nodiscard]] bool IsKeyReleased(Key key) override;

        private:
            GLFWwindow* mx_window{nullptr};
    };

    class OpenGLMouseInput final : public MouseInput
    {
        public:
            [[nodiscard]] static int GetMouseX() { return 0;};
            [[nodiscard]] static int GetMouseY() { return 0;};
            //bool IsMouseButtonPressed(MouseButton button) const;
    };
}

