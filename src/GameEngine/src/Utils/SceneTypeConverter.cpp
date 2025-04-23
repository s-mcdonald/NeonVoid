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

#include <stdexcept>
#include <string>
#include <unordered_map>

#include <NeonEngine/Types.hpp>
#include <NeonEngine/SceneTypeConverter.hpp>

namespace Neon
{
    const std::unordered_map<std::string, SceneType> SceneTypeConverter::stringToEnum = {
        {"Title", SceneType::Title},
        {"Menu", SceneType::Menu},
        {"Gameplay", SceneType::Gameplay},
        {"Pause", SceneType::Pause}
    };

    const std::unordered_map<SceneType, std::string> SceneTypeConverter::enumToString = {
        {SceneType::Title, "Title"},
        {SceneType::Menu, "Menu"},
        {SceneType::Gameplay, "Gameplay"},
        {SceneType::Pause, "Pause"}
    };

    namespace
    {
        template <typename MapType, typename KeyType, typename ValueType>
        bool FindInMap(const MapType& map, const KeyType& key, ValueType& value)
        {
            auto it = map.find(key);
            if (it != map.end())
            {
                value = it->second;
                return true;
            }
            return false;
        }
    }

    bool SceneTypeConverter::TryParse(const std::string& str, SceneType& outType)
    {
        return FindInMap(stringToEnum, str, outType);
    }

    bool SceneTypeConverter::IsValid(const std::string& str)
    {
        SceneType temp;
        return FindInMap(stringToEnum, str, temp);
    }

    SceneType SceneTypeConverter::Parse(const std::string& str)
    {
        try
        {
            return stringToEnum.at(str);
        }
        catch (const std::out_of_range&)
        {
            throw std::runtime_error("Unable to convert string to SceneType.");
        }
    }

    std::string SceneTypeConverter::ToString(SceneType type)
    {
        return enumToString.at(type);
    }
};
