
#pragma once

namespace Neon
{
    enum class Key
    {
        Unknown = 0,
        A,
        B,
        C,
        D,
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
        Escape,
        Enter,
        Space,
        Backspace,
        Tab,
        LeftShift,
        RightShift,
        LeftCtrl,
        RightCtrl,
        LeftAlt,
        RightAlt,
        Up,
        Down,
        Left,
        Right,
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
        // ...
    };

    class KeyboardInput : public Input
    {
        public:
            [[nodiscard]] bool IsKeyPressed(Key key) const;
            [[nodiscard]] bool IsKeyHeld(Key key) const;
            [[nodiscard]] bool IsKeyReleased(Key key) const;
    };

    class MouseInput : public Input
    {
        public:
            [[nodiscard]] int GetMouseX() const;
            [[nodiscard]] int GetMouseY() const;
            //bool IsMouseButtonPressed(MouseButton button) const;
    };
}

