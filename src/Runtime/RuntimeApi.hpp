/**
 * {SourceHeader}
 */

#pragma once

#include <string>

#include <Runtime/ExtRuntime.hpp>

namespace Neon
{
    typedef void* WindowHandlePtr;
    class IPlatform;
    class IRenderer;
    class IVertexBuffer;
    class IShader;

    class RuntimeApi
    {
        public:
            RuntimeApi(const RuntimeApi&) = delete;
            RuntimeApi& operator=(const RuntimeApi&) = delete;
            static RuntimeApi& GetInstance();

        public:
            static IPlatform* CreatePlatform();
            [[nodiscard]] IRenderer* GetRenderer() const;

            static IVertexBuffer* CreateVertexBuffer(float* vertices, size_t size) ;
            static IShader* CreateShader(std::string vertexPath, std::string fragmentPath);

            void SetWindow(WindowHandlePtr window);
            [[nodiscard]] WindowHandlePtr GetWindowAsPtr() const;

        private:
            RuntimeApi();
            ~RuntimeApi();

        private:
            WindowHandlePtr mx_window{nullptr};
            IRenderer* m_renderer;
    };
}
