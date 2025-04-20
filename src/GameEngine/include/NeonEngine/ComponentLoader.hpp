/**
 * {SourceHeader}
 */

#pragma once

#include <unordered_map>

#include <NeonEngine/Types.hpp>
#include <NeonEngine/Components.hpp>

namespace Neon
{
    class ComponentLoader
    {
        public:
            static std::unordered_map<std::string, Component*> CollectComponents(std::vector<YComponent> components);
    };
}
