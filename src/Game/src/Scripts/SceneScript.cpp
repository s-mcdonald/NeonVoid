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

#include <queue>
#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

#include <GameScripts.hpp>
#include <NeonEngine/All.hpp>

// Make this a value on the MyGame app.
static float s_lastSpawnTime        = 0.0f;
static float s_enemyLastSpawnTime   = 0.0f;

std::function<void(Neon::Scene* scene)> SceneScript::GetLevelOneInitScript()
{
    return[](Neon::Scene* scene)
    {
        Neon::Entity* mainPlayer = nullptr;
        auto hasError = false;

        // Make/Create Scene level components
        if (!scene->MakeComponent("sceneCompBackgroundSound"))  { std::cerr << "Failed to create sceneCompBackgroundSound" << std::endl; hasError = true;   }
        if (!scene->MakeComponent("sceneCompCherrySound"))      { std::cerr << "Failed to create sceneCompCherrySound" << std::endl; hasError = true;       }
        if (!scene->MakeComponent("sceneCompBombSound"))        { std::cerr << "Failed to create sceneCompBombSound" << std::endl; hasError = true;       }

        if (!scene->MakeComponent("sceneCompText"))             { std::cerr << "Failed to create sceneCompText" << std::endl; hasError = true;              }
        if (!scene->MakeComponent("sceneCompShader"))           { std::cerr << "Failed to create sceneCompShader" << std::endl; hasError = true;            }
        if (!scene->MakeComponent("sceneCompTimer"))            { std::cerr << "Failed to create sceneCompTimer" << std::endl; hasError = true;             }

        mainPlayer = scene->MakeEntity("mainPlayer");

        if (mainPlayer == nullptr)
        {
            hasError = true;
        }

        if (hasError)
        {
            return;
        }

        // get reference to components and start ticking
        auto* timerComponent = static_cast<Neon::TimerComponent*>(scene->GetComponent("sceneCompTimer"));
        auto* backgroundSoundComp = scene->GetComponentByTag<Neon::AudioComponent>("sceneCompBackgroundSound");
        auto* munchSound = scene->GetComponentByTag<Neon::AudioComponent>("sceneCompCherrySound");
        auto* bombSound = scene->GetComponentByTag<Neon::AudioComponent>("sceneCompBombSound");

        auto* playerScore = mainPlayer->GetComponentByTag<Neon::ScoreComponent>("playerScore");

        backgroundSoundComp->TriggerPlayRepeat();
        timerComponent->Start();

        auto* collisionComponent = mainPlayer->GetComponent<Neon::CollisionComponent>();
        collisionComponent->OnCollision([scene, mainPlayer, playerScore, munchSound, bombSound](Neon::Entity* other)
        {
            if (playerScore == nullptr)
            {
                std::cout << "Failed to get player score" << std::endl;
                return;
            }

            if (munchSound == nullptr)
            {
                std::cout << "Failed to get munch sound" << std::endl;
                return;
            }

            if (bombSound == nullptr)
            {
                std::cout << "Failed to get munch sound" << std::endl;
                return;
            }

            if (other->GetType() == Neon::EntityType::HealthPack)
            {
                playerScore->AddScore(10);

                Neon::Score score = playerScore->GetScore();

                munchSound->TriggerPlayOnce();

                scene->GetComponentByTag<Neon::TextComponent>("sceneCompText")->SetText("Score " + std::to_string(score));

                scene->DestroyEntity(other);
            }

            if (other->GetType() == Neon::EntityType::Enemy)
            {
                playerScore->SubScore(10);

                Neon::Score score = playerScore->GetScore();

                bombSound->TriggerPlayOnce();

                if (score < 0)
                {
                    // game over
                    score = 0;
                    // scene->DestroyEntity(mainPlayer);
                    scene->GetComponentByTag<Neon::TextComponent>("sceneCompText")->SetText("Game - Over");
                }
                else
                {
                    scene->GetComponentByTag<Neon::TextComponent>("sceneCompText")->SetText("Score " + std::to_string(score));
                }

                scene->DestroyEntity(other);
            }
        });
    };
}

std::function<void(Neon::Scene* scene)> SceneScript::GetLevelOneUpdateScript()
{
    return[](Neon::Scene* scene)
    {
        // ..
    };
}

std::function<void(Neon::Scene* scene)> SceneScript::GetSceneTimerScript()
{
    std::vector<GameEntityConfig> bombPositions;
    std::vector<GameEntityConfig> cherryPositions;

    bombPositions.emplace_back(GameEntityConfig{ {-0.9, 1.0}, false });
    bombPositions.emplace_back(GameEntityConfig{ {-0.8, 1.0}, true });
    bombPositions.emplace_back(GameEntityConfig{ {-0.7, 1.0}, false });
    bombPositions.emplace_back(GameEntityConfig{ {-0.6, 1.0}, true });
    bombPositions.emplace_back(GameEntityConfig{ {-0.5, 1.0}, true });
    bombPositions.emplace_back(GameEntityConfig{ {-0.4, 1.0}, false });
    bombPositions.emplace_back(GameEntityConfig{ {-0.3, 1.0}, false });
    bombPositions.emplace_back(GameEntityConfig{ {-0.2, 1.0}, true });
    bombPositions.emplace_back(GameEntityConfig{ {-0.1, 1.0}, true });

    bombPositions.emplace_back(GameEntityConfig{ {  0.0, 1.0}, true });

    bombPositions.emplace_back(GameEntityConfig{ {  0.1, 1.0}, false });
    bombPositions.emplace_back(GameEntityConfig{ {  0.2, 1.0}, true });
    bombPositions.emplace_back(GameEntityConfig{ {  0.3, 1.0}, false });
    bombPositions.emplace_back(GameEntityConfig{ {  0.4, 1.0}, false });
    bombPositions.emplace_back(GameEntityConfig{ {  0.5, 1.0}, false });
    bombPositions.emplace_back(GameEntityConfig{ {  0.6, 1.0}, true });
    bombPositions.emplace_back(GameEntityConfig{ {  0.7, 1.0}, false });
    bombPositions.emplace_back(GameEntityConfig{ {  0.8, 1.0}, false });
    bombPositions.emplace_back(GameEntityConfig{ {  0.9, 1.0}, true });

    // Cherry Data

    cherryPositions.emplace_back(GameEntityConfig{ {-1.0, -1.0}, true });
    cherryPositions.emplace_back(GameEntityConfig{ {-0.9, -1.0}, true });
    cherryPositions.emplace_back(GameEntityConfig{ {-0.8, -1.0}, false });
    cherryPositions.emplace_back(GameEntityConfig{ {-0.7, -1.0}, true });
    cherryPositions.emplace_back(GameEntityConfig{ {-0.6, -1.0}, true });
    cherryPositions.emplace_back(GameEntityConfig{ {-0.5, -1.0}, true });
    cherryPositions.emplace_back(GameEntityConfig{ {-0.4, -1.0}, false });
    cherryPositions.emplace_back(GameEntityConfig{ {-0.3, -1.0}, true });
    cherryPositions.emplace_back(GameEntityConfig{ {-0.2, -1.0}, true });
    cherryPositions.emplace_back(GameEntityConfig{ {-0.1, -1.0}, true });
    cherryPositions.emplace_back(GameEntityConfig{ {  0.0,-1.0}, true });
    cherryPositions.emplace_back(GameEntityConfig{ {  0.1,-1.0}, false });
    cherryPositions.emplace_back(GameEntityConfig{ {  0.2,-1.0}, true });
    cherryPositions.emplace_back(GameEntityConfig{ {  0.3,-1.0}, true });
    cherryPositions.emplace_back(GameEntityConfig{ {  0.4,-1.0}, false });
    cherryPositions.emplace_back(GameEntityConfig{ {  0.5,-1.0}, false });
    cherryPositions.emplace_back(GameEntityConfig{ {  0.6,-1.0}, true });
    cherryPositions.emplace_back(GameEntityConfig{ {  0.7,-1.0}, false });
    cherryPositions.emplace_back(GameEntityConfig{ {  0.8,-1.0}, true });
    cherryPositions.emplace_back(GameEntityConfig{ {  0.9,-1.0}, true });
    cherryPositions.emplace_back(GameEntityConfig{ {  1.0,-1.0}, true });


    return[cherryPositions, bombPositions](Neon::Scene* scene) mutable
    {

        // Create a random number generator
        std::random_device rd; // Seed for randomness
        std::mt19937 g(rd());  // Mersenne Twister random number generator

        // Shuffle the vector
        std::shuffle(bombPositions.begin(), bombPositions.end(), g);
        std::shuffle(cherryPositions.begin(), cherryPositions.end(), g);


        auto* timerComponent = scene->GetComponentByTag<Neon::TimerComponent>("sceneCompTimer");
        float elapsedTime = timerComponent->GetElapsedTime();

        if (false == cherryPositions.empty() && std::abs(elapsedTime - s_lastSpawnTime - CHERRY_SPAWN_INTERVAL) < INTERVAL_TOLERANCE)
        {
            auto* cherry = scene->MakeEntity("cherryHealthPack");
            auto* position = cherry->GetComponent<Neon::PositionComponent>();


            auto& pd = cherryPositions.front();
            position->SetPoint(pd.point);


            // cherryPositions.erase(cherryPositions.begin());
            cherry->SetUserFlag(BOMB_FLAG_SPEED_FAST, pd.fast);

            s_lastSpawnTime = elapsedTime;
        }

        if (false == bombPositions.empty() && std::abs(elapsedTime - s_enemyLastSpawnTime - CHERRY_BOMB_INTERVAL) < INTERVAL_TOLERANCE)
        {
            auto* bomb = scene->MakeEntity("bombEnemy");
            auto* position = bomb->GetComponent<Neon::PositionComponent>();
            auto& pd = bombPositions.front(); // Get the front point in the queue
            position->SetPoint(pd.point);
            //bombPositions.erase(bombPositions.begin()); // Remove the processed point from the queue

            bomb->SetUserFlag(BOMB_FLAG_SPEED_FAST, pd.fast);

            s_enemyLastSpawnTime = elapsedTime;
        }
    };
}
