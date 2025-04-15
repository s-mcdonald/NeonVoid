/**
 * {SourceHeader}
 */

#include <iostream>

#include <NeonEngine/Entity/Entity.hpp>
#include <NeonEngine/GameEngine.hpp>
#include <NeonEngine/Components/Components.hpp>

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

        m_buffer = GameEngine::CreateVertexBuffer(m_vertices.data(), m_vertices.size() * sizeof(float));

        m_buffer->Bind();

        m_buffer->Unbind();
    }

    void ShaderComponent::OnUpdate()
    {
        Point p{};

        if (GetParentEntity() != nullptr && GetParentEntity()->HasComponent<PositionComponent>())
        {
            auto* pos = GetParentEntity()->GetComponent<PositionComponent>();
            p = pos->GetPoint();

#ifdef NEON_DEBUG_KB_INPUT
            std::cout << "[DEBUG](Sahder) NEW: x: " << p.x << " y: " << p.y << "\n";
#endif

            for (size_t i = 0; i < m_vertices.size(); i += 2) {
                m_vertices[i] += p.x;
                m_vertices[i + 1] += p.y;
            }

            UpdateData(m_vertices);
        }
        else
        {
            p.x = 0.0f;
            p.y = 0.0f;
        }

        const auto& api = GameEngineApi::getInstance();

        // auto m_modelMatrix = glm::mat4(1.0f);
        // // Update the model transformation matrix to translate by (x, y)
        // m_modelMatrix = glm::mat4(1.0f); // Reset to identity
        // m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(p.x , p.y, 0.0f)); // Apply translation
        //
        // glUseProgram(m_shader->GetShaderProgramId());
        //
        // GLint uniformLoc = glGetUniformLocation(m_shader->GetShaderProgramId(), "modelMatrix");
        // glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &m_modelMatrix[0][0]);


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
