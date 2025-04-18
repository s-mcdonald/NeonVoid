/**
 * {SourceHeader}
 */

#pragma once

#include <vector>

#include <NeonRuntime/ShaderFactory.hpp>
#include <NeonRuntime/BufferFactory.hpp>

namespace Neon
{
    class RuntimeApi
    {
        public:
            RuntimeApi(const RuntimeApi&) = delete;
            RuntimeApi& operator=(const RuntimeApi&) = delete;
            static RuntimeApi& GetInstance();

            static IPlatform* CreatePlatform();
            [[nodiscard]] IRenderer* GetRenderer() const;
            [[nodiscard]] static std::vector<float> GenerateCircleVertices(float radius, int segments) ;

            IVertexBuffer* CreateVertexBuffer(float* vertices, size_t size);
            IShader* CreateShader(const std::string& vertexPath, const std::string& fragmentPath);

        private:
            RuntimeApi();
            ~RuntimeApi();

        private:
            WindowHandlePtr mx_window{nullptr};
            IRenderer* m_renderer;
            ShaderFactory m_shaderFactory;
            BufferFactory m_bufferFactory;
    };
}
