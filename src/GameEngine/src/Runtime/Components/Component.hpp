#pragma once

namespace Neon
{
    class Component
    {
        public:
            Component() = default;
            virtual ~Component() = default;

            virtual void OnInit() = 0;
            virtual void OnUpdate() = 0;
            virtual void OnDestroy() = 0;
    };
}
