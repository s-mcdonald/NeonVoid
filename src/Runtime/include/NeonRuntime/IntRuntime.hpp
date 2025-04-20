/**
 * {SourceHeader}
 */

#pragma once

#include <cmath>
#include <cstddef>
#include <string>
#include <vector>

#ifdef NEON_BUILD_OPENGL

#include <NeonRuntime/Backends/OpenGLHeaders.hpp>
#include <NeonRuntime/ExtRuntime.hpp>
#include <NeonRuntime/ShaderFactory.hpp>
#include <NeonRuntime/Backends/OpenGL.hpp>
#include <NeonRuntime/Backends/OpenGLInput.hpp>
#include <NeonRuntime/Backends/OpenGLRenderer.hpp>
#include <NeonRuntime/Backends/OpenGLShader.hpp>
#include <NeonRuntime/Backends/OpenGLVertexBuffer.hpp>
#include <NeonRuntime/RuntimeApi.hpp>

#elif defined(NEON_BUILD_VULKAN)

#else

#endif