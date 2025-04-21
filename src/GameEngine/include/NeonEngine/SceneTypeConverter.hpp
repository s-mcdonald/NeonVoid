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

#include <unordered_map>
#include <string>

#include <NeonEngine/Types.hpp>

namespace Neon
{
    class SceneTypeConverter
    {
        public:
            static SceneType Parse(const std::string& str);
            static bool TryParse(const std::string& str, SceneType& outType);
            static bool IsValid(const std::string& str);
            static std::string ToString(SceneType type);

        public:
            static const std::unordered_map<std::string, SceneType> stringToEnum;
            static const std::unordered_map<SceneType, std::string> enumToString;
    };
};
