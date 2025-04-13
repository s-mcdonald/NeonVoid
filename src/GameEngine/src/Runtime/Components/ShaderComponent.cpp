
#include <glm/gtc/matrix_transform.hpp>

#include <Runtime/Runtime.hpp>
#include <Runtime/Components/Components.hpp>
#include <Runtime/Engine/Shader.hpp>
#include <Runtime/Engine/Backends/OpenGL/GameEngineApi.hpp>

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
        const auto& api = GameEngineApi::getInstance();

        api.GetRenderer()->RenderCircle(m_shader->GetShaderProgramId(), m_buffer->GetVao(), m_vertices.size());
    }

    void ShaderComponent::UpdateData(const std::vector<float>& vertices)
    {
        m_vertices = vertices;

        m_buffer->UpdateData(m_vertices.data(), m_vertices.size() * sizeof(float));
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
