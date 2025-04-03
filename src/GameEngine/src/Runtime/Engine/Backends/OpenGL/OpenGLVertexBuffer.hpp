/**
 *
 */
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../../../Runtime/Runtime.hpp"

namespace Neon
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
        public:
            OpenGLVertexBuffer(const float* vertices, size_t size);
            ~OpenGLVertexBuffer();

            void Bind() const override;
            void Unbind() const override;
            void UpdateData(const void* data, size_t size) override;

            GLuint GetVao() override;

        private:
            GLuint m_VAO{}, m_VBO{};
    };
}
