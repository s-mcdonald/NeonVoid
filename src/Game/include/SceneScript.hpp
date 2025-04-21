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
                    if (scene->GetPlayerEntity())
                    {
                        std::cout << "We found the main player" << std::endl;
                    }
                    else
                    {
                        std::cout <<"We dont have a player entity" << std::endl;
                    }
                };
            }
    };
}

