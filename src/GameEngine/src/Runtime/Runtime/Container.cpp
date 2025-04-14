/**
 * {SourceHeader}
 */

#include <Runtime/Runtime/Container.hpp>
#include <Runtime/Types.hpp>

namespace Neon
{
    Container& Container::GetInstance()
    {
        static Container instance;
        return instance;
    }

    void Container::SetWindow(WindowHandlePtr window)
    {
        mx_window = window;
    }

    WindowHandlePtr Container::GetWindowAsPtr() const
    {
        return mx_window;
    }
}
