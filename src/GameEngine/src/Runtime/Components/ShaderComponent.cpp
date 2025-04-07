/**
 * 
 */

#include "Runtime/Runtime.hpp"
#include "Runtime/Engine/Shader.hpp"

namespace Neon 
{
    ShaderComponent::~ShaderComponent()
    {
        OnDestroy();

        if (m_shader)
        {
            delete m_shader;
            m_shader = nullptr;
        }
    }

    void ShaderComponent::OnInit()
    {
        m_shader->OnInit();

        m_buffer = GameEngine::CreateVertexBuffer(m_vertices.data(), m_vertices.size() * sizeof(float));

        m_buffer->Bind();

        m_buffer->Unbind();
    }

    void ShaderComponent::OnUpdate()
    {
        // hmm, not sure if we should prob use events instead.
        auto& api = GameEngineApi::getInstance();

        // refactor to send the Buffer and the Shader as ref
        api.GetRenderer()->RenderCircle(m_shader->GetShaderProgramId(), m_buffer->GetVao(), m_vertices.size());
    }

    void ShaderComponent::OnDestroy()
    {
        if (m_shader)
        {
            m_shader->OnDelete();
        }

        if (m_buffer)
        {
            delete m_buffer;
            m_buffer = nullptr;
        }
    }
}
