/**
 * {SourceHeader}
 */

#pragma once

#include <string>

#include <Runtime/ExtRuntime.hpp>

namespace Neon
{
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

        private:
            RuntimeApi();
            ~RuntimeApi();

        private:
            WindowHandlePtr mx_window{nullptr};
            IRenderer* m_renderer;
    };
}
