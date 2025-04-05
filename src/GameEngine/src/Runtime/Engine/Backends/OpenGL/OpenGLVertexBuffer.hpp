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
            OpenGLVertexBuffer(const float*, size_t);
            ~OpenGLVertexBuffer() override;

            void Bind() const override;
            void Unbind() const override;
            void UpdateData(const void* data, size_t size) override;

            GLuint GetVao() override;

        private:
            const float* m_vertices;
            size_t m_size;
            GLuint m_VAO{};
            GLuint m_VBO{};
    };
}
