/**
 * {SourceHeader}
 */

#pragma once

#include <functional>

namespace Neon
{
    class SceneScript
    {
        public:
            static std::function<void()> GetUpdateScript()
            {
                return []()
                {
                    std::cout << "Hello World! from the custom script." << std::endl;
                };
            }
    };
}

