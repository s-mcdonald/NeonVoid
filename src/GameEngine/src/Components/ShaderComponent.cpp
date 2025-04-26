/**
 *    ███╗   ██╗███████╗ ██████╗ ███╗   ██╗
 *    ████╗  ██║██╔════╝██╔═══██╗████╗  ██║
 *    ██╔██╗ ██║█████╗  ██║   ██║██╔██╗ ██║
 *    ██║╚██╗██║██╔══╝  ██║   ██║██║╚██╗██║
 *    ██║ ╚████║███████╗╚██████╔╝██║ ╚████║
 *    ╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═══╝
 * ========================================
 *                 NeonVoid
 *         A 2D Game Engine in C++
 * ----------------------------------------
 * License: MIT
 * Copyright (c) : 2024 Sam McDonald
 * Repository: https://github.com/s-mcdonald/NeonVoid
 */

#ifdef NEON_DEBUG
#include <iostream>
#endif

#include <NeonEngine/Entity.hpp>
#include <NeonEngine/Components.hpp>

namespace Neon 
{
    ShaderComponent::~ShaderComponent()
    {
        OnDestroy();

        if (m_buffer)
        {
            delete m_buffer;
            m_buffer = nullptr;
        }

        if (m_shader)
        {
            delete m_shader;
            m_shader = nullptr;
        }
    }

    void ShaderComponent::OnInit()
    {
        m_shader->Bind();

        m_shader->OnInit();

        m_buffer = RuntimeApi::GetInstance().CreateVertexBuffer(m_vertices.data(),m_indicies.data(),  m_vertices.size() * sizeof(float));

        m_buffer->Bind();

        m_buffer->Unbind();
    }

    void ShaderComponent::OnUpdate()
    {
        if (GetParentEntity() != nullptr && GetParentEntity()->HasComponent<PositionComponent>())
        {
            auto* pos = GetParentEntity()->GetComponent<PositionComponent>();
            Point p = pos->GetPoint();

            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(p.x, p.y, 0.0f));

            m_shader->Bind();
            m_shader->SetUniformMat4("modelMatrix", modelMatrix);
            m_shader->Unbind();
        }

        RuntimeApi::GetInstance().GetRenderer()->RenderTriangle(
            m_shader->GetShaderProgramId(),
            m_buffer->GetVao(),
            m_vertices.size()
        );
    }

    void ShaderComponent::OnDestroy()
    {
        if (m_shader)
        {
            m_shader->Unbind();
            m_shader->OnDelete();
        }
    }
}
