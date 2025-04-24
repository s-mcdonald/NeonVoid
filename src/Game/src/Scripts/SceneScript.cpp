/**
 *    ███╗   ██╗███████╗ ██████╗ ███╗   ██╗
 *    ████╗  ██║██╔════╝██╔═══██╗████╗  ██║
 *    ██╔██╗ ██║█████╗  ██║   ██║██╔██╗ ██║
 *    ██║╚██╗██║██╔══╝  ██║   ██║██║╚██╗██║
 *    ██║ ╚████║███████╗╚██████╔╝██║ ╚████║
 *    ╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═══╝
 * ========================================
 *                 NeonVoid
 *         A 2D Game Engine in C++
 * ----------------------------------------
 * License: MIT
 * Copyright (c) : 2024 Sam McDonald
 * Repository: https://github.com/s-mcdonald/NeonVoid
 */

#include <functional>
#include <iostream>

#include <NeonEngine/All.hpp>
#include <GameScripts.hpp>

std::function<void(Neon::Scene* scene)> SceneScript::GetLevelOneInitScript()
{
    return[](Neon::Scene* scene)
    {
        Neon::Entity* mainPlayer = nullptr;

        if (scene->MakeComponent("sceneCompCherrySound"))
        {
            std::cout << "sceneCompCherrySound" << std::endl;
        }

        if (scene->MakeComponent("sceneCompTimer"))
        {
            auto timer = static_cast<Neon::TimerComponent*>(scene->GetComponent("sceneCompTimer"));

            timer->Start();

            std::cout << "Render sceneCompTimer" << std::endl;
        }

        if (scene->MakeComponent("sceneCompBackgroundSound"))
        {
            std::cout << "Render sceneCompBackgroundSound" << std::endl;
        }

        if (scene->MakeComponent("sceneCompText"))
        {
            std::cout << "Render sceneCompText" << std::endl;
        }

        if (scene->MakeComponent("sceneCompShader"))
        {
            std::cout << "Render sceneCompShader" << std::endl;
        }

        if (mainPlayer = scene->MakeEntity("mainPlayer"))
        {
            std::cout << "Created Player Entity" << std::endl;
        }

        if (scene->MakeEntity("cherryHealthPack"))
        {
            std::cout << "Created Cherry" << std::endl;
        }

        if (scene->MakeEntity("bombEnemy"))
        {
            std::cout << "Bomb Cherry" << std::endl;
        }


        auto* collisionComponent = mainPlayer->GetComponent<Neon::CollisionComponent>();
        collisionComponent->OnCollision([scene, mainPlayer](Neon::Entity* other)
        {
            if (other->GetType() == Neon::EntityType::HealthPack)
            {
                try
                {
                    mainPlayer->GetComponentByTag<Neon::ScoreComponent>("playerScore")->AddScore(10);
                    Neon::Score score = mainPlayer->GetComponentByTag<Neon::ScoreComponent>("playerScore")->GetScore();


                    std::cout << "Start to play: " << std::endl;
                    scene->GetComponentByTag<Neon::AudioComponent>("sceneCompCherrySound")->TriggerPlayOnce();

                    std::cout << "End to play: " << std::endl;
                    scene->GetComponentByTag<Neon::TextComponent>("sceneCompText")->SetText("Score " + std::to_string(score));
                    scene->DestroyEntity(other);

                }
                catch (std::exception& e)
                {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                catch (...)
                {
                    std::cout << "Unknown Error" << std::endl;
                }


                //
            }

        });
    };
}

std::function<void(Neon::Scene* scene)> SceneScript::GetLevelOneUpdateScript()
{
    return[](Neon::Scene* scene)
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

std::function<void(Neon::Scene* scene)> SceneScript::GetSceneTimerScript()
{
    return[](Neon::Scene* scene)
    {
        std::cout << "Scene Timer real callback here..." << std::endl;
    };
}
