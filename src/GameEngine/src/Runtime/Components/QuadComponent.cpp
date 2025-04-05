/**
 * 
 */
#include <iostream>
#include <cmath>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    QuadComponent::~QuadComponent()
    {
        OnDestroy();
    }

    void QuadComponent::OnInit()
    {
        m_buffer = GameEngine::CreateVertexBuffer(m_vertices.data(), m_vertices.size() * sizeof(float));

        m_buffer->Bind();

        // Compile and link shaders
        const char* vertexSource = R"(
            #version 330 core
            layout(location = 0) in vec2 position;
            void main() {
                gl_Position = vec4(position, 0.0f, 1.0f);
            })";

        const char* fragmentSource = R"(
            #version 330 core
            out vec4 FragColor;
            void main() {
                FragColor = vec4(0.4f, 0.7f, 0.2f, 1.0f);
            })";

        m_shaderProgram = OpenGL::CreateShaderProgram(vertexSource, fragmentSource);

        m_buffer->Unbind();
    }

    void QuadComponent::OnUpdate() 
    {
        // hmm, not sure if we should prob use events instead.
        auto& api = GameEngineApi::getInstance();

        api.GetRenderer()->RenderQuad(m_shaderProgram, m_buffer->GetVao());
        std::cout << "QuadComponent::m_VAO: " << m_buffer->GetVao() << "\n";
    }

    void QuadComponent::OnDestroy()
    {
        if (m_shaderProgram)
        {
            glDeleteProgram(m_shaderProgram);
            m_shaderProgram = 0;
        }

        if (m_buffer)
        {
            delete m_buffer;
            m_buffer = nullptr;
        }
    }
}
