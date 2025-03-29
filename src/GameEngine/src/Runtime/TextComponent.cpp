/**
 * 
 */
#include <iostream>
#include <cmath>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    TextComponent::TextComponent(const std::string& text, int fontSize) 
        : Component()
        , m_text(text)
        , m_fontSize(fontSize)
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "TextComponent::Constructor called\n";
        #endif

        if (m_fontSize <= 0) 
        {
            m_fontSize = 12;
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

    int TextComponent::GetFontSize() const 
    { 
        return m_fontSize; 
    }

    void TextComponent::SetFontSize(int fontSize) 
    {
        m_fontSize = fontSize; 
    }
}
