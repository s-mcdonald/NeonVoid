/**
 * {SourceHeader}
 */

#pragma once

namespace Neon
{
    class IPlatform;
    class PlatformFactory
    {
        public:
            PlatformFactory() = default;
            ~PlatformFactory() = default;
        public:
            static IPlatform* CreatePlatform();
    };
}

