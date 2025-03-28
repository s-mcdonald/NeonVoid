/**
 * 
 */
#include <iostream>
#include <cmath>

#include "../../GameEngine/src/Runtime/Runtime.hpp"

namespace Neon
{
    class TitleScene : public Scene
    {
        public:
            TitleScene(Platform* platform)
                : Scene(platform) {}
            ~TitleScene() {}

        public:
            void OnInit() override {};
            void OnUpdate() override {};
            bool IsInitialized() const { return true;};
    };
}
