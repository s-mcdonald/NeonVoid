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

#include <NeonRuntime/IRenderer.hpp>

namespace Neon
{
    struct Character {
        unsigned int TextureID;  // ID handle of the glyph texture
        glm::ivec2   Size;       // Size of glyph
        glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
        unsigned int Advance;    // Offset to advance to next glyph
    };

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
            void RenderText(uint32_t shaderProgram, ITextBuffer* textBuffer, const std::string& text) override;

            void LoadFont(const std::string& fontPath) override;

        private:
            std::map<char, Character> m_characters; // prob move this away from the renderer so each TextComp can have its own texture
            FT_Library m_ft{};
            FT_Face m_face{};
    };
}
