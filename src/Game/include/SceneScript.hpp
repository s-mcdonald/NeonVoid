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
            static std::function<void(Scene* scene)> GetUpdateScript()
            {
                return[](Scene* scene)
                {
                    // if (scene->GetComponent("mainPlayer"))
                    // {
                    //     std::cout << "Hello World! from the custom script." << std::endl;
                    // }
                    // else
                    // {
                    //     std::cout <<"We dont have a bomb" << std::endl;
                    // }
                };
            }
    };
}

