/**
 * {SourceHeader}
 */

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Neon
{
    class Container
    {
        public:
            Container(const Container&) = delete;
            Container& operator=(const Container&) = delete;

        public:
            static Container& GetInstance();
            void SetWindow(GLFWwindow*);
            [[nodiscard]] GLFWwindow& GetWindow() const;

            Container(): mx_window(nullptr) {};
            ~Container() = default;

        private:
            GLFWwindow* mx_window{nullptr};
    };
}
