/**
 * {SourceHeader}
 */

#include <Runtime/Backends/OpenGL/OpenGLRenderer.hpp>

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

    void GameEngineApi::RenderQuad(const uint32_t shaderProgram, const uint32_t VAO) const
    {
        m_renderer->RenderQuad(shaderProgram, VAO);
    }

    void GameEngineApi::RenderCircle(const uint32_t shaderProgram, const uint32_t VAO, const int vertexCount) const
    {
        m_renderer->RenderCircle(shaderProgram, VAO, vertexCount);
    }
}
