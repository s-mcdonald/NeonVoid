/**
 * {SourceHeader}
 */

#include <NeonRuntime/BufferFactory.hpp>
#include <NeonRuntime/IntRuntime.hpp>

namespace Neon
{
    IVertexBuffer* BufferFactory::CreateVertexBuffer(float* vertices, size_t size)
    {
#ifdef NEON_BUILD_OPENGL
        return new OpenGLVertexBuffer(vertices, size);
#elif defined(NEON_BUILD_VULKAN)
        return nullptr;
#else
        return nullptr;
#endif
    }
}
