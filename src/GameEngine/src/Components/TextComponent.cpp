/**
 * {SourceHeader}
 */

#include <iostream>
#include <utility>

#include <Components/Components.hpp>

namespace Neon 
{
    TextComponent::TextComponent(const std::string& text) 
        : TextComponent(text, NV_DEFAULT_FONT_SIZE, Point{0, 0}, ColorAlpha{1,1,1,1})
    {
        //
    }

    TextComponent::TextComponent(const std::string& text, float fontSize) 
        : TextComponent(text, fontSize, Point{0, 0}, ColorAlpha{1,1,1,1})
    {
        //
    }

    TextComponent::TextComponent(const std::string& text, float fontSize, const Point& point) 
        : TextComponent(text, fontSize, point, ColorAlpha{1,1,1,1})
    {
        //
    }

    TextComponent::TextComponent(std::string  text, float fontSize, const Point& point, ColorAlpha color)
        : Component()
        , m_text(std::move(text))
        , m_fontSize(fontSize)
        , m_point(point)
        , m_colorAlpha(color)
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
