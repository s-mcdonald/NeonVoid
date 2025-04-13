/**
 * {SourceHeader}
 */

#pragma once

#include <deque>
#include <functional>

#include <Runtime/Types.hpp>
#include <Runtime/AssetManager/AssetManager.hpp>
#include <Runtime/Audio/AudioSystem.hpp>
#include <Runtime/Audio/Volume.hpp>

#include <Runtime/Scene/Scene.hpp>
#include <Runtime/Components/Components.hpp>

#include <Runtime/Runtime/Backends/OpenGL/GameEngineApi.hpp>
#include <Runtime/Runtime/Backends/OpenGL/OpenGLRenderer.hpp>
#include <Runtime/Runtime/Backends/OpenGL/OpenGLVertexBuffer.hpp>
#include <Runtime/Runtime/Backends/VertexBuffer.hpp>
#include <Runtime/Runtime/Shader.hpp>
#include "GameEngine.hpp"
#include "Runtime/Runtime/Backends/IRenderer.hpp"
#include "Runtime/Runtime/Backends/Platform.hpp"
