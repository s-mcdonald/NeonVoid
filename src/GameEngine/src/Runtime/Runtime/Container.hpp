/**
 * {SourceHeader}
 */

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Runtime/Types.hpp>

namespace Neon
{
    class Container
    {
        public:
            Container(const Container&) = delete;
            Container& operator=(const Container&) = delete;

        public:
            static Container& GetInstance();
            void SetWindow(WindowHandlePtr);
            [[nodiscard]] WindowHandlePtr GetWindowAsPtr() const;

            Container(): mx_window(nullptr) {};
            ~Container() = default;

        private:
            WindowHandlePtr mx_window{nullptr};
    };
}
