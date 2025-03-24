/**
 * 
 */
#include <iostream>
#include <cmath>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    Component::Component() 
        : IRenderable()
    {
        std::cout << "Component::Constructor called\n";
    }

    Component::~Component() 
    {
        std::cout << "Component::Destructor called\n";
    }

    void Component::Init() 
    {
        if (m_initFunc) 
        {
            m_initFunc();
        }
    }

    void Component::Render() 
    {
        if (m_renderFunc) 
        {
            m_renderFunc(); 
        }
    }
    
    const std::vector<float>& Component::GetVertices() const 
    {
        return m_vertices;
    }

    void Component::SetInitFunction(InitFunction initFunc) 
    {
        m_initFunc = initFunc;
    }
    
    void Component::SetRenderFunction(RenderFunction renderFunc) 
    {
        m_renderFunc = renderFunc;
    }
    
    void Component::SetVertices(const std::vector<float>& vertices) 
    {
        m_vertices = vertices;
    }
}
