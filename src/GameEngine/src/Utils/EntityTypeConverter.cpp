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
#include <NeonEngine/EntityTypeConverter.hpp>

namespace Neon
{
    const std::unordered_map<std::string, EntityType> EntityTypeConverter::stringToEnum = {
        {"Player", EntityType::Player},
        {"Enemy", EntityType::Enemy},
        {"HealthPack", EntityType::HealthPack},
    };

    const std::unordered_map<EntityType, std::string> EntityTypeConverter::enumToString = {
        {EntityType::Player, "Player"},
        {EntityType::Enemy, "Enemy"},
        {EntityType::HealthPack, "HealthPack"},
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

    bool EntityTypeConverter::TryParse(const std::string& str, EntityType& outType)
    {
        return FindInMap(stringToEnum, str, outType);
    }

    bool EntityTypeConverter::IsValid(const std::string& str)
    {
        EntityType temp;
        return FindInMap(stringToEnum, str, temp);
    }

    EntityType EntityTypeConverter::Parse(const std::string& str)
    {
        try
        {
            return stringToEnum.at(str);
        }
        catch (const std::out_of_range&)
        {
            throw std::runtime_error("Unable to convert string to EntityType.");
        }
    }

    std::string EntityTypeConverter::ToString(EntityType type)
    {
        return enumToString.at(type);
    }
};
