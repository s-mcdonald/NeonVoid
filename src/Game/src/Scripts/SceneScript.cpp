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

#include <GameScripts.hpp>
#include <NeonEngine/All.hpp>
#include <queue>

// Make this a value on the MyGame app.
static float s_lastSpawnTime        = 0.0f;

std::function<void(Neon::Scene* scene)> SceneScript::GetLevelOneInitScript()
{
    return[](Neon::Scene* scene)
    {
        Neon::Entity* mainPlayer = nullptr;

        if (scene->MakeComponent("sceneCompBackgroundSound"))
        {
            scene->GetComponentByTag<Neon::AudioComponent>("sceneCompBackgroundSound")->TriggerPlayRepeat();
        }

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

        if (scene->MakeEntity("bombEnemy"))
        {
            std::cout << "Bomb Cherry" << std::endl;
        }

        auto* collisionComponent = mainPlayer->GetComponent<Neon::CollisionComponent>();
        collisionComponent->OnCollision([scene, mainPlayer](Neon::Entity* other)
        {
            if (other->GetType() == Neon::EntityType::HealthPack)
            {
                auto* playerScore = mainPlayer->GetComponentByTag<Neon::ScoreComponent>("playerScore");
                if (playerScore == nullptr)
                {
                    std::cout << "Failed to get player score" << std::endl;
                    return;
                }

                std::cout << "Add to score" << std::endl;
                playerScore->AddScore(10);

                Neon::Score score = playerScore->GetScore();

                std::cout << "Trigger" << std::endl;
                auto* munchSound = scene->GetComponentByTag<Neon::AudioComponent>("sceneCompCherrySound");
                if (munchSound == nullptr)
                {
                    std::cout << "Failed to get munch sound" << std::endl;
                }
                else
                {
                    std::cout << "Trigger Sound" << std::endl;
                    munchSound->TriggerPlayOnce();
                }

                scene->GetComponentByTag<Neon::TextComponent>("sceneCompText")->SetText("Score " + std::to_string(score));

                scene->DestroyEntity(other);
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
    std::vector<Neon::Point> cherryPositions;
    cherryPositions.emplace_back(0.10, 0.5);
    cherryPositions.emplace_back(0.20, -0.5);
    cherryPositions.emplace_back(0.30, 0.6);
    cherryPositions.emplace_back(0.40, -0.4);
    cherryPositions.emplace_back(0.50, -0.2);
    cherryPositions.emplace_back(0.50, -0.2);
    cherryPositions.emplace_back(0.50, -0.2);
    cherryPositions.emplace_back(0.50, -0.2);
    cherryPositions.emplace_back(0.50, -0.2);

    return[cherryPositions](Neon::Scene* scene) mutable
    {
        if (cherryPositions.empty())
        {
            // perhaps we trigger end of game
            return;
        }

        auto* timerComponent = scene->GetComponentByTag<Neon::TimerComponent>("sceneCompTimer");
        if (timerComponent == nullptr)
        {
            return;
        }

        float elapsedTime = timerComponent->GetElapsedTime();
        if (std::abs(elapsedTime - s_lastSpawnTime - CHERRY_SPAWN_INTERVAL) > INTERVAL_TOLERANCE)
        {
            return;
        }

        auto* cherry = scene->MakeEntity("cherryHealthPack");
        if (cherry == nullptr)
        {
            return;
        }

        auto* position = cherry->GetComponent<Neon::PositionComponent>();
        if (position == nullptr)
        {
            return;
        }

        Neon::Point p = cherryPositions.front(); // Get the front point in the queue

        Neon::Point p2;
        p2.x = p.x;
        p2.y = p.y;
        position->SetPoint(p2);

        cherryPositions.erase(cherryPositions.begin()); // Remove the processed point from the queue

        s_lastSpawnTime = elapsedTime;
    };
}
