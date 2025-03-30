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

    IRenderer* GameEngineApi::GetRenderer()
    {
        return m_renderer;
    }

    void GameEngineApi::RenderQuad(GLuint shaderProgram, GLuint VAO) 
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "GameEngineApi::RenderQuad called\n";
        #endif

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glBindVertexArray(0);
    }
}