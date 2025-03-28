/**
 * 
 */
#include <iostream>
#include <cmath>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    Component::Component() 
        : IComponent()
        , m_VAO(0)
        , m_VBO(0)
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "Component::Constructor called\n";
        #endif
    }

    Component::~Component() 
    {
        if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
        if (m_VBO) glDeleteBuffers(1, &m_VBO);
        if (m_shaderProgram) glDeleteProgram(m_shaderProgram);

        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "Component::Destructor completed\n";
        #endif
    }

    void Component::OnInit() 
    {
        if (m_initFunc) 
        {
            m_initFunc();
        }
    }

    void Component::OnUpdate() 
    {
        if (m_renderFunc) 
        {
            m_renderFunc(); 
        }
    }

    void Component::SetInitFunction(InitFunction initFunc) 
    {
        m_initFunc = initFunc;
    }
    
    void Component::SetRenderFunction(RenderFunction renderFunc) 
    {
        m_renderFunc = renderFunc;
    }
}
