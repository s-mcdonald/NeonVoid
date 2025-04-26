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

#include <fstream>
#include <iostream>
#include <map>
#include <memory>

#include <NeonRuntime/Backends/OpenGLHeaders.hpp>
#include <NeonRuntime/Backends/OpenGLRenderer.hpp>
#include <NeonRuntime/Backends/OpenGLVertexBuffer.hpp>

// @todo : this class needs work!
namespace Neon 
{
    OpenGLRenderer::~OpenGLRenderer()
    {
        if (m_face)
        {
            FT_Done_Face(m_face);
        }

        if (m_ft)
        {
            FT_Done_FreeType(m_ft);
        }
    }


    void OpenGLRenderer::Clear()
    {
        glClearColor(0.3f,0.3f,0.3f, 1.0f);
        glClearColor(0.2f,0.2f,0.5f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLRenderer::Reset()
    {
        glFlush();
    }

    void OpenGLRenderer::BeginFrame()
    {
        glClearColor(0.0f,0.0f,0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void OpenGLRenderer::EndFrame()
    {
        glFlush();
    }

    void OpenGLRenderer::RenderTriangle(const GLuint shaderProgram, const GLuint VAO, const GLsizei vertexCount)
    {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        glBindVertexArray(0);
    }

    void OpenGLRenderer::RenderText(const GLuint shaderProgram, ITextBuffer* textBuffer, DrawTextMeta textData)
    {
        glUseProgram(shaderProgram);
        glUniform3f(glGetUniformLocation(shaderProgram, "textColor"),  textData.rgb.r, textData.rgb.b, textData.rgb.b);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(textBuffer->GetVao());

        // glm::mat4 projection = glm::ortho(0.0f, 1920.0f, .0f, 1080.0f);
        glm::mat4 projection = glm::ortho(0.0f, textData.orthoProjection.right, .0f, textData.orthoProjection.top);
        glUniformMatrix4fv(
            glGetUniformLocation(shaderProgram, "projection"),
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );

        // iterate through all characters
        std::string::const_iterator c;
        for (c = textData.text.begin(); c != textData.text.end(); ++c)
        {
            Character ch = m_characters[*c];

            float xpos = textData.x + ch.Bearing.x * textData.scale;
            float ypos = textData.y - (ch.Size.y - ch.Bearing.y) * textData.scale;

            float w = ch.Size.x * textData.scale;
            float h = ch.Size.y * textData.scale;
            // update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, textBuffer->GetVbo());
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for the next glyph (note that advance is the number of 1/64 pixels)
            textData.x += (ch.Advance >> 6) * textData.scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // code from: https://learnopengl.com/In-Practice/Text-Rendering
    void OpenGLRenderer::LoadFont(const std::string& fontPath)
    {
        if (FT_Init_FreeType(&m_ft))
        {
            std::cerr << "[DEBUG]::FREETYPE: Could not init FreeType Library" << std::endl;
            return;
        }

        if (FT_New_Face(m_ft, fontPath.c_str(), 0, &m_face))
        {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            return;
        }

        FT_Set_Pixel_Sizes(m_face, 0, 48);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (unsigned char c = 0; c < 128; c++)
        {
            if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);   // this is the textureID when we need to abstract it
                                            // So right now we can only have 1 font
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                m_face->glyph->bitmap.width,
                m_face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                m_face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
                glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
                m_face->glyph->advance.x
            };
            m_characters.insert(std::pair<char, Character>(c, character));
        }
    }
}
