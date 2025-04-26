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

#if defined(NEON_DEBUG)
#include <iostream>
#endif

#include <utility>

#include <NeonEngine/Components.hpp>

namespace Neon 
{
    TextComponent::TextComponent(const std::string& tag, std::string text, IShader* shader)
        : Component(tag)
        , m_text(std::move(text))
        , m_shader(shader)
    {
        // ..
    }

    TextComponent::~TextComponent()
    {
        m_text.clear();

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

    void TextComponent::OnInit()
    {
        m_shader->Bind();

        m_shader->OnInit();

        size_t glyphSize = 96; // 96 bytes per glyph
        size_t bufferSize = m_text.size() * glyphSize;

        m_buffer = RuntimeApi::GetInstance().CreateTextBuffer(bufferSize);

        m_buffer->Init();
        m_buffer->Bind();
        m_buffer->Unbind();

        std::cout << "TextComponent Initialization Done" << std::endl;
    }

    // changes throughout the game here
    void TextComponent::OnUpdate() 
    {
        // m_buffer->SetText(m_text);
        // m_buffer->SetScale(0.5f);
        // m_buffer->SetPos(m_point);
        // m_buffer->SetColor(m_rgb);
        // m_buffer->SetOrtho(m_ortho);

        // set th data here and pass the buffer into the renderer OnRender
    }

    void TextComponent::OnRender()
    {
        DrawTextMeta textData;
        textData.text = m_text;
        textData.x = m_pos_x;
        textData.y = m_pos_y;

        RuntimeApi::GetInstance().GetRenderer()->RenderText(
            m_shader->GetShaderProgramId(),
            m_buffer,
            textData
        );
    }

    void TextComponent::OnDestroy()
    {
        if (m_shader)
        {
            m_shader->Unbind();
            m_shader->OnDelete();
        }
    }

    void TextComponent::SetPosition(float x, float y)
    {
        m_pos_x = x;
        m_pos_y = y;
    }
}
