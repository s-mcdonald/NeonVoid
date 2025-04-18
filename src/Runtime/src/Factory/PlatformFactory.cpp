/**
 * {SourceHeader}
 */

#include <NeonRuntime/IntRuntime.hpp>
#include <NeonRuntime/PlatformFactory.hpp>

namespace Neon
{
    IPlatform* PlatformFactory::CreatePlatform()
    {
#ifdef NEON_BUILD_OPENGL
        return new Neon::OpenGL();
#elif defined(NEON_BUILD_VULKAN)
        //
#else
        return nullptr;
#endif
    }
}
