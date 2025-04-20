/**
 * {SourceHeader}
 */

#include <stdexcept>
#include <string>
#include <unordered_map>

#include <NeonEngine/EntityTypeConverter.hpp>
#include <NeonEngine/Types.hpp>

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

    bool EntityTypeConverter::TryParse(const std::string& str, EntityType& outType)
    {
        auto it = EntityTypeConverter::stringToEnum.find(str);
        if (it != EntityTypeConverter::stringToEnum.end())
        {
            outType = it->second;
            return true;
        }
        return false;
    }

    bool EntityTypeConverter::IsValid(const std::string& str)
    {
        auto it = EntityTypeConverter::stringToEnum.find(str);
        if (it != EntityTypeConverter::stringToEnum.end())
        {
            return true;
        }
        return false;
    }

    EntityType EntityTypeConverter::Parse(const std::string& str)
    {
        auto it = EntityTypeConverter::stringToEnum.find(str);
        if (it != EntityTypeConverter::stringToEnum.end())
        {
            return it->second;
        }
        throw std::runtime_error("Unable to convert string to EntityType.");
    }

    std::string EntityTypeConverter::ToString(EntityType type)
    {
        auto it = enumToString.find(type);
        if (it != enumToString.end())
        {
            return it->second;
        }
        throw std::runtime_error("Unable to convert EntityType to string.");
    }
};
