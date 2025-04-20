/**
 * {SourceHeader}
 */

#pragma once

#include <cstddef>

#ifdef NEON_BUILD_OPENGL

#include <NeonRuntime/IShader.hpp>
#include <NeonRuntime/IWindow.hpp>
#include <NeonRuntime/IInput.hpp>
#include <NeonRuntime/IPlatform.hpp>
#include <NeonRuntime/IRenderer.hpp>
#include <NeonRuntime/IVertexBuffer.hpp>
#include <NeonRuntime/RuntimeApi.hpp>

#elif defined(NEON_BUILD_VULKAN)

#else

#endif