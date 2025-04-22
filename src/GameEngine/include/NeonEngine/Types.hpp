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
#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace Neon
{
    typedef uint16_t ViewPortDimension;
    typedef uint16_t WindowDimension;
    typedef uint32_t EntityID;
    typedef uint32_t Score;
    typedef short Health;

    ///
    /// Player / Entity IDs
    ///
    constexpr EntityID MAIN_PLAYER_ENTITY_ID = 1;
    constexpr EntityID START_NEXT_ENTITY_ID = 5;

    typedef void* WindowHandlePtr;

    constexpr float MIN_FONT_SIZE = 8;
    constexpr float BASE_FONT_SIZE = 18;
    constexpr float MULTIPLIER_RESOLUTION = 1;

    constexpr float NV_DEFAULT_FONT_SIZE = BASE_FONT_SIZE * MULTIPLIER_RESOLUTION;
    constexpr float NV_MINIMUM_FONT_SIZE = MIN_FONT_SIZE * MULTIPLIER_RESOLUTION;

    constexpr float ViewPortRatio_1_1 = 1.0f;             // Square 1:1
    constexpr float ViewPortRatio_4_3 = 4.0f / 3.0f;      // Aspect ratio (4:3)
    constexpr float ViewPortRatio_16_9 = 16.0f / 9.0f;    // Aspect ratio (16:9)
    constexpr float ViewPortRatio_16_10 = 16.0f / 10.0f;  // Aspect ratio (16:10)
    constexpr float ViewPortRatio_21_9 = 21.0f / 9.0f;    // Ultra-wide aspect ratio (21:9)
    constexpr float ViewPortRatio_32_9 = 32.0f / 9.0f;    // Super ultra-wide aspect ratio (32:9)

    constexpr inline auto DefaultAudioVolume = 50.00f;

    constexpr inline auto DirectionDeltaUp = 0.008f;
    constexpr inline auto DirectionDeltaDown = -0.008f;
    constexpr inline auto DirectionDeltaLeft = -0.010f;
    constexpr inline auto DirectionDeltaRight = 0.010f;

    // Physx
    constexpr inline auto NV_Friction           = 0.0005f;
    constexpr inline auto NV_Acceleration       = 0.015f;
    constexpr inline auto NV_Deceleration       = 0.010f;
    constexpr inline auto NV_MAX_Velocity       = 0.01f;
    constexpr inline auto NV_MIN_Velocity       = 0.0001f; // on slowdown, stop once gets to this level
    constexpr inline auto NV_FULL_Velocity      = 1.00f;
    constexpr inline auto NV_ZERO_Velocity      = 0.00f;

    constexpr inline auto MaxSpeed = 0.2f;

    constexpr inline auto targetFps = 60.0f;
    constexpr inline auto deltaTime = 1.0f / targetFps;

    typedef struct
    {
            bool repeat = false;
            uint8_t delayMs = 0;
            uint8_t volume = 30;
    } AudioConfig;

    struct Point
    {
            float x;
            float y;
    };

    enum class SceneType
    {
        Title = 0,
        Menu,
        Gameplay,
        Pause
    };

    enum class EntityType
    {
        Player,
        Enemy,
        HealthPack
    };

    enum class ScriptType
    {
        None                = 0, // this would be an error in some circumstances
        SceneInit           = 1,
        SceneUpdate         = 2,
        EntityUpdate        = 3,
    };

    // @todo: Add a layer to each component + entity
    // component.layer = Layer::Foreground;
    enum class Layer : short
    {
        Background  = 0,
        Middle      = 5,
        Foreground  = 10
    };

    enum class Direction
    {
        None = 0,
        Up,
        Right,
        Down,
        Left,

        UpLeft,
        UpRight,
        DownLeft,
        DownRight,
    };

    // need a better name for this struct
    struct YShader
    {
        std::string name;
        std::string layer;
        std::string dir;
        std::string vertexShader;
        std::string fragShader;
        std::vector<float> vertices;
    };

    struct YPosConfigData
    {
        Point p{0,0};
    };

    struct YAudioConfigData
    {
        std::string path;
        bool loop = false;
        uint8_t volume = 30;
    };

    struct YTextConfigData
    {
        std::string text;
    };

    enum class ConfigType {
        None = 0,
        Movement,
        Shader,
        Audio,
        Position,
        Text,
        Script
    };

    struct YComponent
    {
        std::string name;
        std::string type;

        ConfigType configType = ConfigType::None;

        union
        {
            YShader* shaderConfig;
            YAudioConfigData* audioConfig;
            YPosConfigData* posConfig;
        };

        YTextConfigData textConfig;

        YComponent() : shaderConfig(nullptr)
        {
            // ..
        }
    };

    struct YEntity
    {
        std::string name;
        EntityType type;
        std::vector<YComponent> components;
    };

    struct YScene {
        SceneType sceneType;
        std::vector<YComponent> scripts;
        std::vector<YComponent> components;
        std::vector<YEntity> entities;
    };

    class Component;

    struct MComp
    {
        std::string type{};
        Component* mx_comp{nullptr};
    };
}
