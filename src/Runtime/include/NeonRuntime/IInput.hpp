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

#include <NeonRuntime/Backends/OpenGLHeaders.hpp>

namespace Neon
{
    typedef void* WindowHandlePtr;

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
            Input() = delete;
            explicit Input(const WindowHandlePtr windowHandle) : mx_window(windowHandle) {};
            virtual ~Input() = default;
        private:
            WindowHandlePtr mx_window{nullptr};
    };

    class KeyboardInput : public Input
    {
        public:
            explicit KeyboardInput(const WindowHandlePtr windowHandle) : Input(windowHandle) {};
            ~KeyboardInput() override = default;

        public:
            virtual bool IsKeyPressed(Key key) = 0;
            virtual bool IsKeyHeld(Key key) = 0;
            virtual bool IsKeyReleased(Key key) = 0;
    };

    class MouseInput : public Input
    {
        public:
            explicit MouseInput(const WindowHandlePtr windowHandle) : Input(windowHandle) {};
            ~MouseInput() override = default;
            [[nodiscard]] static int GetMouseX() { return 0;};
            [[nodiscard]] static int GetMouseY() { return 0;};
    };
}

