/**
 * {SourceHeader}
 */

#include <stdexcept>
#include <string>
#include <unordered_map>

#include <NeonEngine/SceneTypeConverter.hpp>
#include <NeonEngine/Types.hpp>

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

    bool SceneTypeConverter::TryParse(const std::string& str, SceneType& outType)
    {
        auto it = SceneTypeConverter::stringToEnum.find(str);
        if (it != SceneTypeConverter::stringToEnum.end())
        {
            outType = it->second;
            return true;
        }
        return false;
    }

    bool SceneTypeConverter::IsValid(const std::string& str)
    {
        auto it = SceneTypeConverter::stringToEnum.find(str);
        if (it != SceneTypeConverter::stringToEnum.end())
        {
            return true;
        }
        return false;
    }

    SceneType SceneTypeConverter::Parse(const std::string& str)
    {
        auto it = SceneTypeConverter::stringToEnum.find(str);
        if (it != SceneTypeConverter::stringToEnum.end())
        {
            return it->second;
        }
        throw std::runtime_error("Unable to convert string to SceneType.");
    }

    std::string SceneTypeConverter::ToString(SceneType type)
    {
        auto it = enumToString.find(type);
        if (it != enumToString.end())
        {
            return it->second;
        }
        throw std::runtime_error("Unable to convert SceneType to string.");
    }
};
