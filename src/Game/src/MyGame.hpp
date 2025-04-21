/**
 * {SourceHeader}
 */

#pragma once

#include <NeonEngine/All.hpp>

#include <SceneScript.hpp>

namespace Neon
{
    class MyGame final : public Application
    {
        public:
            MyGame()
            {
                // we could also make the FR as part of Application!!!!\
                // we can do that later
                FunctionRegistry::Get().Register("Scene::Foo", SceneScript::GetUpdateScript());

                // @todo: Use a filesystem lib to parse filenames
                SetSceneYaml("./assets/game.yaml");
            }

            [[nodiscard]] bool Initialize()
            {
                return Application::Initialize(800, 600, "Neon Void (0.0.5)");
            }
    };
}
