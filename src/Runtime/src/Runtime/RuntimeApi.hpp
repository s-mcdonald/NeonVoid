/**
 * {SourceHeader}
 */

#pragma once

#include <string>

#include <Runtime/ExtRuntime.hpp>

namespace Neon
{
    typedef void* WindowHandlePtr;

    class RuntimeApi
    {
        public:
            RuntimeApi(const RuntimeApi&) = delete;
            RuntimeApi& operator=(const RuntimeApi&) = delete;

        public:
            static RuntimeApi& GetInstance();

        public:
            static IPlatform* CreatePlatform();
            [[nodiscard]] IRenderer* GetRenderer() const;

            IVertexBuffer* CreateVertexBuffer(float* vertices, size_t size);
            IShader* CreateShader(std::string vertexPath, std::string fragmentPath);

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
