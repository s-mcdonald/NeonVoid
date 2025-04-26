/**
 *    ███╗   ██╗███████╗ ██████╗ ███╗   ██╗
 *    ████╗  ██║██╔════╝██╔═══██╗████╗  ██║
 *    ██╔██╗ ██║█████╗  ██║   ██║██╔██╗ ██║
 *    ██║╚██╗██║██╔══╝  ██║   ██║██║╚██╗██║
 *    ██║ ╚████║███████╗╚██████╔╝██║ ╚████║
 *    ╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═══╝
 * ========================================
 *                 NeonVoid
 *         A 2D Game Engine in C++
 * ----------------------------------------
 * License: MIT
 * Copyright (c) : 2024 Sam McDonald
 * Repository: https://github.com/s-mcdonald/NeonVoid
 */

#pragma once

#include <map>

#include <NeonRuntime/RTTypes.hpp>
#include <NeonRuntime/IRenderer.hpp>

namespace Neon
{
    class OpenGLRenderer final : public IRenderer
    {
        public:
            OpenGLRenderer() = default;
            ~OpenGLRenderer() override;

            static void Clear();
            static void Reset();

            void BeginFrame() override;
            void EndFrame() override;
            void RenderTriangle(uint32_t shaderProgram, uint32_t VAO, int vertexCount) override;
            void RenderQuad(uint32_t shaderProgram, uint32_t VAO, int vertexCount) override;
            void RenderText(uint32_t shaderProgram, ITextBuffer* textBuffer, const DrawTextMeta textData) override;

            void LoadFont(const std::string& fontPath) override;

        private:
            std::map<char, Character> m_characters; // moves this away from the renderer so each TextComp can have its own texture
            FT_Library m_ft{};
            FT_Face m_face{};
    };
}
