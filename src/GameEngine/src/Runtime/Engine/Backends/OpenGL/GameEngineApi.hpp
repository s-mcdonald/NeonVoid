#pragma once

namespace Neon
{
    class GameEngineApi
    {
        public:
        GameEngineApi(const GameEngineApi&) = delete;
        GameEngineApi& operator=(const GameEngineApi&) = delete;

        void RenderQuad(uint32_t shaderProgram, uint32_t VAO) const;
        void RenderCircle(uint32_t shaderProgram, uint32_t VAO, int vertexCount) const;

        public:
        static GameEngineApi& getInstance();

        [[nodiscard]] IRenderer* GetRenderer() const;

        private:
        GameEngineApi();
        ~GameEngineApi();

        private:
        IRenderer* m_renderer;
    };
}