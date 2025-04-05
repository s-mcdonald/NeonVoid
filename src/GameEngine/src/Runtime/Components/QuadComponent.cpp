/**
 * 
 */
#include <iostream>
#include <cmath>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    QuadComponent::QuadComponent() 
        : Component()
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "QuadComponent::Constructor called\n";
        #endif
    }

    // @todo: Abstract this to platforms
    QuadComponent::~QuadComponent() 
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "QuadComponent::Destructor completed\n";
        #endif

        OnDestroy();
    }

    void QuadComponent::OnInit()
    {
        float vertices[] = {
            0.0f,  0.5f,        // Top vertex
            -0.5f, -0.5f,       // Bottom left
            0.5f, -0.5f,        // Bottom right
        };

        m_buffer = GameEngine::CreateVertexBuffer(vertices, sizeof(vertices) );

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
