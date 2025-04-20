/**
 * {SourceHeader}
 */

#pragma once

#include <unordered_map>
#include <string>

#include <NeonEngine/Types.hpp>

namespace Neon
{
    class EntityTypeConverter
    {
        public:
            static EntityType Parse(const std::string& str);
            static bool TryParse(const std::string& str, EntityType& outType);
            static bool IsValid(const std::string& str);
            static std::string ToString(EntityType type);

        public:
            static const std::unordered_map<std::string, EntityType> stringToEnum;
            static const std::unordered_map<EntityType, std::string> enumToString;
    };
};
