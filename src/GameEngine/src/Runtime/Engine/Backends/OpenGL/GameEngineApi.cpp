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

    // src/GameEngine/src/Runtime/Engine/Backends/OpenGL/OpenGLRenderer::RenderQuad
    void GameEngineApi::RenderQuad(const GLuint shaderProgram, const GLuint VAO)
    {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glBindVertexArray(0);
    }

    // src/GameEngine/src/Runtime/Engine/Backends/OpenGL/OpenGLRenderer::RenderCircle
    void GameEngineApi::RenderCircle(const GLuint shaderProgram, const GLuint VAO, const GLsizei vertexCount)
    {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
        glBindVertexArray(0);
    }
}