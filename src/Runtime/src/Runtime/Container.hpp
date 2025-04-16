/**
 * {SourceHeader}
 */

#pragma once

#include <string>

#include <Runtime/Backends/IShader.hpp>

#ifdef NEON_BUILD_OPENGL
#include <Runtime/Backends/OpenGL/OpenGL.hpp>
#include <Runtime/Backends/OpenGL/OpenGLShader.hpp>
#include <Runtime/Backends/OpenGL/OpenGLVertexBuffer.hpp>
#elif defined(NEON_BUILD_VULKAN)
#else
#endif

namespace Neon
{
    typedef void* WindowHandlePtr;

    ///
    /// Rename to Renderer API
    ///
    class Container
    {
        public:
            Container(const Container&) = delete;
            Container& operator=(const Container&) = delete;

        public:
            static Container& GetInstance()
            {
                static Container instance;
                return instance;
            }

            static IPlatform* CreatePlatform()
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

            IVertexBuffer* CreateVertexBuffer(float* vertices, size_t size)
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

            IShader* CreateShader(std::string vertexPath, std::string fragmentPath)
            {
#ifdef NEON_BUILD_OPENGL
                return new OpenGLShader(std::move(vertexPath), std::move(fragmentPath));
#elif defined(NEON_BUILD_VULKAN)
                // send back the Vulkan Shader
#else
                return nullptr;
#endif
            }

            void SetWindow(WindowHandlePtr window)
            {
                mx_window = window;
            }

            [[nodiscard]] WindowHandlePtr GetWindowAsPtr() const
            {
                return mx_window;
            }

            Container(): mx_window(nullptr) {};
            ~Container() = default;

        private:
            WindowHandlePtr mx_window{nullptr};
    };
}
