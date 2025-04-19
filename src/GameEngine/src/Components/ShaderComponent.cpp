/**
 * {SourceHeader}
 */

#include <iostream>

#include <NeonEngine/Entity.hpp>
#include <NeonEngine/Components.hpp>

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
        // Bind should be before the loop for the shader
        m_shader->Bind();

        m_shader->OnInit();

        m_buffer = RuntimeApi::GetInstance().CreateVertexBuffer(m_vertices.data(), m_vertices.size() * sizeof(float));

        m_buffer->Bind();

        m_buffer->Unbind();
    }

    void ShaderComponent::OnUpdate()
    {
        if (GetParentEntity() != nullptr && GetParentEntity()->HasComponent<PositionComponent>())
        {
            auto* pos = GetParentEntity()->GetComponent<PositionComponent>();

            Point p{};
            p = pos->GetPoint();

#ifdef NEON_DEBUG_KB_INPUT
            std::cout << "[DEBUG](Sahder) NEW: x: " << p.x << " y: " << p.y << "\n";
#endif

            for (size_t i = 0; i < m_vertices.size(); i += 2)
            {
                m_vertices[i] += p.x;
                m_vertices[i + 1] += p.y;
            }

            UpdateData(m_vertices);
        }

        RuntimeApi::GetInstance().GetRenderer()->RenderCircle(m_shader->GetShaderProgramId(), m_buffer->GetVao(), m_vertices.size());
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
            // UnBind should be after the loop for the shader
            m_shader->Unbind();
            m_shader->OnDelete();
        }

        if (m_buffer)
        {
            delete m_buffer;
            m_buffer = nullptr;
        }
    }
}
