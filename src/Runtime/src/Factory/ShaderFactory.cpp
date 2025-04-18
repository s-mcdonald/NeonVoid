/**
 * {SourceHeader}
 */

#include <NeonRuntime/ShaderFactory.hpp>
#include <NeonRuntime/IntRuntime.hpp>

namespace Neon
{
    IShader* ShaderFactory::CreateShader(std::string vertexPath, std::string fragmentPath)
    {
#ifdef NEON_BUILD_OPENGL
        return new OpenGLShader(std::move(vertexPath), std::move(fragmentPath));
#elif defined(NEON_BUILD_VULKAN)
        // send back the Vulkan Shader
#else
        return nullptr;
#endif
    }
}
