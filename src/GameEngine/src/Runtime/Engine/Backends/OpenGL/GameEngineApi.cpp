/**
 * 
 */

#include "Runtime/Runtime.hpp"

#include <iostream>

namespace Neon
{
    GameEngineApi& GameEngineApi::getInstance() 
    {
        static GameEngineApi instance;
        return instance;
    }

    GameEngineApi::GameEngineApi() 
    {
        m_renderer = new OpenGLRenderer();
    }

    GameEngineApi::~GameEngineApi() 
    {
        delete m_renderer;
    }

    IRenderer* GameEngineApi::GetRenderer() const
    {
        return m_renderer;
    }

    void GameEngineApi::RenderQuad(const GLuint shaderProgram, const GLuint VAO) const
    {
        m_renderer->RenderQuad(shaderProgram, VAO);
    }

    void GameEngineApi::RenderCircle(const GLuint shaderProgram, const GLuint VAO, const GLsizei vertexCount) const
    {
        m_renderer->RenderCircle(shaderProgram, VAO, vertexCount);
    }
}