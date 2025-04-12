
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Neon
{
    // @todo refactor/abstract to use diff codes based on backend..
    enum class Key
    {
        Unknown = 0,
        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Num0,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,
        Escape =  GLFW_KEY_ESCAPE,
        Enter =  GLFW_KEY_ENTER,
        Space,
        Backspace = GLFW_KEY_SPACE,
        Tab,
        LeftShift,
        RightShift,
        LeftCtrl,
        RightCtrl,
        LeftAlt,
        RightAlt,
        Up = GLFW_KEY_UP,
        Down = GLFW_KEY_DOWN,
        Left = GLFW_KEY_LEFT,
        Right = GLFW_KEY_RIGHT,
        Function1,
        Function2,
        Function3,
        Function4,
        Function5,
        Function6,
        Function7,
        Function8,
        Function9,
        Function10,
        Function11,
        Function12,
        MouseLeftButton,
        MouseRightButton,
        MouseMiddleButton
    };

    class Input
    {
        public:
            Input() = default;
            virtual ~Input() = default;
    };

    class KeyboardInput final : public Input
    {
        public:
            KeyboardInput() = delete;
            explicit KeyboardInput(GLFWwindow* window)
                : Input()
                , mx_window(window)
            {
                //
            };
            ~KeyboardInput() override = default;

        public:
            [[nodiscard]] static bool IsKeyPressed(Key key) ;
            [[nodiscard]] static bool IsKeyHeld(Key key) ;
            [[nodiscard]] static bool IsKeyReleased(Key key) ;

        private:
            GLFWwindow* mx_window{nullptr};
    };

    class MouseInput final : public Input
    {
        public:
            [[nodiscard]] static int GetMouseX() { return 0;};
            [[nodiscard]] static int GetMouseY() { return 0;};
            //bool IsMouseButtonPressed(MouseButton button) const;
    };
}

