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
    TextComponent::TextComponent(const std::string& text, IShader* shader)
        : Component()
        , m_text(std::move(text))
        , m_shader(shader)
    {
        if (m_fontSize <= NV_MINIMUM_FONT_SIZE)
        {
            m_fontSize = NV_MINIMUM_FONT_SIZE;
        }
    }

    TextComponent::~TextComponent()
    {
        m_text.clear();
        m_fontSize = 0.0f;
        if (m_shader) m_shader;
        m_shader = nullptr;
    }

    void TextComponent::OnUpdate() 
    {
       /////////// RuntimeApi::GetInstance().GetRenderer()->RenderText(m_shader->GetShaderProgramId(), m_text );
    }

    const std::string& TextComponent::GetText() const 
    { 
        return m_text; 
    }

    void TextComponent::SetText(const std::string& text) 
    { 
        m_text = text;
    }

    float TextComponent::GetFontSize() const 
    { 
        return m_fontSize; 
    }

    void TextComponent::SetFontSize(float fontSize) 
    {
        m_fontSize = fontSize; 
    }

    Point TextComponent::GetPosition() const
    {
        return m_point;
    }
}
