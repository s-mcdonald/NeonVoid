/**
 * {SourceHeader}
 */

#pragma once

#include <Runtime/Types.hpp>

namespace Neon
{
    class Container
    {
        public:
            Container(const Container&) = delete;
            Container& operator=(const Container&) = delete;

        public:
            static Container& GetInstance()
            {
                static Container instance;
                return instance;
            }

            void SetWindow(WindowHandlePtr window)
            {
                mx_window = window;
            }

            [[nodiscard]] WindowHandlePtr GetWindowAsPtr() const
            {
                return mx_window;
            }

            Container(): mx_window(nullptr) {};
            ~Container() = default;

        private:
            WindowHandlePtr mx_window{nullptr};
    };
}
