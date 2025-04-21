/**
 * {SourceHeader}
 */

#pragma once

#include <cstdint>
#include <vector>

namespace Neon
{
    ///
    /// Player / Entity IDs
    ///
    constexpr uint8_t MAIN_PLAYER = 1;

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

    typedef uint16_t ViewPortDimension;
    typedef uint16_t WindowDimension;
    typedef uint32_t EntityID;
    typedef uint32_t Score;
    typedef short Health;

    constexpr inline auto DefaultAudioVolume = 50.00f;

    constexpr inline auto DirectionDeltaUp = 0.008f;
    constexpr inline auto DirectionDeltaDown = -0.008f;
    constexpr inline auto DirectionDeltaLeft = -0.008f;
    constexpr inline auto DirectionDeltaRight = 0.008f;

    constexpr inline auto Deceleration = 0.01f;

    constexpr inline auto MaxSpeed = 0.2f;

    constexpr inline auto targetFps = 120.0f;
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

    enum class EntityType {
        Player,
        Enemy,
        HealthPack
    };

    // @todo: Add a layer to each component + entity
    // component.layer = Layer::Foreground;
    enum class Layer : short
    {
        Background = 0,
        Middle = 5,
        Foreground = 10
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
        std::vector<YComponent> components;
        std::vector<YEntity> entities;
    };
}
