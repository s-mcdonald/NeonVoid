/**
 * {SourceHeader}
 */

#include <iostream>
#include <utility>

#include <NeonEngine/Components.hpp>

namespace Neon 
{
    TextComponent::TextComponent(const std::string& text)
        : Component()
        , m_text(std::move(text))
    {
        if (m_fontSize <= NV_MINIMUM_FONT_SIZE)
        {
            m_fontSize = NV_MINIMUM_FONT_SIZE;
        }
    }

    TextComponent::~TextComponent()
    {
#if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
        std::cout << "TextComponent::Destructor completed\n";
#endif
    }

    void TextComponent::OnInit() 
    {
        //
    }

    void TextComponent::OnUpdate() 
    {
        std::cout << "Rendering Text: " << m_text << " with Font Size: " << m_fontSize << std::endl;
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

    void TextComponent::OnDestroy()
    {
        // ....
    }
}
