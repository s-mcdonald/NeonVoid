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
        , m_VAO(0)
        , m_VBO(0)
    {
        std::cout << "Component::Constructor called\n";
    }

    Component::~Component() 
    {
        if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
        if (m_VBO) glDeleteBuffers(1, &m_VBO);
        if (m_shaderProgram) glDeleteProgram(m_shaderProgram);

        std::cout << "Component::Destructor completed\n";
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

    void Component::SetInitFunction(InitFunction initFunc) 
    {
        m_initFunc = initFunc;
    }
    
    void Component::SetRenderFunction(RenderFunction renderFunc) 
    {
        m_renderFunc = renderFunc;
    }
}
