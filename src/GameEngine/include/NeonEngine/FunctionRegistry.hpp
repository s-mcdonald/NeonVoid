/**
 * {SourceHeader}
 */

#pragma once

#include <unordered_map>
#include <functional>
#include <string>

namespace Neon
{
    class FunctionRegistry
    {
        public:
            static FunctionRegistry& Get()
            {
                static FunctionRegistry instance;
                return instance;
            }

            template<typename Func>
            void Register(const std::string& name, Func&& func)
            {
                m_functions[name] = std::forward<Func>(func);
            }

            std::function<void()> Fetch(const std::string& name)
            {
                auto it = m_functions.find(name);
                if (it != m_functions.end())
                {
                    return it->second;
                }
                return nullptr;
            }

        private:
            std::unordered_map<std::string, std::function<void()>> m_functions;
    };
}

