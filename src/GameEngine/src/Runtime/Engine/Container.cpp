
#include <Runtime/Engine/Container.hpp>

namespace Neon
{
    Container& Container::GetInstance()
    {
        static Container instance;
        return instance;
    }

    void Container::SetWindow(GLFWwindow* window)
    {
        mx_window = window;
    }

    GLFWwindow& Container::GetWindow() const
    {
        return *mx_window;
    }
}
