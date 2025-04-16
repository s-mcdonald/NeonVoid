/**
 * {SourceHeader}
 */

#include <string>

#include <Runtime/GameEngineApi.hpp>
#include <Runtime/Backends/OpenGL/OpenGLRenderer.hpp>

namespace Neon
{
    typedef void* WindowHandlePtr;

    GameEngineApi& GameEngineApi::GetInstance()
    {
        static GameEngineApi instance;
        return instance;
    }

    GameEngineApi::GameEngineApi() : mx_window(nullptr)
    {
        m_renderer = new OpenGLRenderer();
    }

    GameEngineApi::~GameEngineApi()
    {
        delete m_renderer;
    }

    IRenderer* GameEngineApi::GetRenderer() const
    {
        return m_renderer;
    }

    void GameEngineApi::SetWindow(WindowHandlePtr window)
    {
        mx_window = window;
    }

    [[nodiscard]] WindowHandlePtr GameEngineApi::GetWindowAsPtr() const
    {
        return mx_window;
    }

    IPlatform* GameEngineApi::CreatePlatform()
    {
#ifdef NEON_BUILD_OPENGL
        // System::GetPlatform()
        return new Neon::OpenGL();
#elif defined(NEON_BUILD_VULKAN)
        //
#else
        return nullptr;
#endif
    }

    IVertexBuffer* GameEngineApi::CreateVertexBuffer(float* vertices, size_t size)
    {
#ifdef NEON_BUILD_OPENGL
        return new OpenGLVertexBuffer(vertices, size);
#elif defined(NEON_BUILD_VULKAN)
        // return new VulkanVertexBuffer(vertices, size);
#else
        // let's also do an assert here, I think cherno did this too.
        // need to learn more about compile time asserts.
        return nullptr;
#endif
    }

    IShader* GameEngineApi::CreateShader(std::string vertexPath, std::string fragmentPath)
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
