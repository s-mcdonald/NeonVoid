/**
 * 
 */
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Runtime/Runtime.hpp"

namespace Neon 
{
    OpenGL::OpenGL() 
        : Platform()
        , m_window(nullptr) 
    {
        std::cout << "OpenGL::Constructor called\n";
    }

    OpenGL::~OpenGL() 
    {
        std::cout << "OpenGL::Destructor called\n";
        CleanResources();
    }

    bool OpenGL::Initialize(int width, int height, const char* title) 
    {
        if (!glfwInit()) 
        {
            std::cerr << "Failed to initialize GLFW!\n";
            return false;
        }

        // Create window
        m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!m_window) 
        {
            std::cerr << "Failed to create GLFW window!\n";
            glfwTerminate();
            return false;
        }

        // Set as the active window, without this it loads in background.
        glfwMakeContextCurrent(m_window);

        glfwSwapInterval(1);

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 

        std::cout << "OpenGL Initialized Successfully!\n";
        return true;
    }

    void OpenGL::Run(Game* game) 
    {
        if (!m_window) return;

        while (!glfwWindowShouldClose(m_window)) 
        {
            glfwPollEvents();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // perhaps the game has scene obj where we can get the current scene and render here.
            // game.GetCurrentScene().OnRender(); ??
            auto* scene = game->GetCurrentScene();
            
            // Render the Scene to OpenGL
            scene->Render();
            //RenderText("Hello, OpenGL!", 50.0f, 500.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

            // Currently...
            // The rendering of the scene will be handled by Scene directly and will be in
            // OpenGL exclusivly. Because we want the abstraction for DX and OpenGL the 
            // Runtime will have funcs like RenderPolygon(), ApplyShader() ... 
            // or whatever. I dont know because I never made a game 
            // before but in due course ill find out.

            // Push to Ogl
            glfwSwapBuffers(m_window);
        }
    }

    void OpenGL::CleanResources() 
    {
        if (m_window) 
        {
            glfwDestroyWindow(m_window);
        }
        glfwTerminate();
    }

    GLuint fontTexture;
    stbtt_bakedchar cdata[96];  // ASCII 32..126 is the range we want to support

    void OpenGL::LoadFont(const char *fontPath) 
    {
        // Load font file into memory
        FILE *fontFile = fopen(fontPath, "rb");
        fseek(fontFile, 0, SEEK_END);
        long fontSize = ftell(fontFile);
        fseek(fontFile, 0, SEEK_SET);
        unsigned char *fontBuffer = (unsigned char *)malloc(fontSize);
        fread(fontBuffer, 1, fontSize, fontFile);
        fclose(fontFile);
    
        // Create a texture atlas for the font
        unsigned char tempBitmap[512 * 512];  // Assuming 512x512 texture size
        stbtt_BakeFontBitmap(fontBuffer, 0, 32.0f, tempBitmap, 512, 512, 32, 96, cdata);
    
        // Create OpenGL texture from the bitmap
        glGenTextures(1, &fontTexture);
        glBindTexture(GL_TEXTURE_2D, fontTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, tempBitmap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    

    // WIP - Compile the vertex and fragment shaders
    // WIP - link them into a program (shaderProgram)
    // WIP - Finally: Setup VAO, VBO for text rendering
    GLuint shaderProgram;
    GLuint VAO, VBO;

    void OpenGL::CompileShaders() 
    {
        //
    }

    void OpenGL::RenderText(const char *text, float x, float y, float scale, glm::vec3 color) 
    {
        glUseProgram(shaderProgram);
        
        // Set text color
        glUniform3f(glGetUniformLocation(shaderProgram, "textColor"), color.r, color.g, color.b);
        
        // Set up model matrix (for positioning text)
        glm::mat4 projection = glm::ortho(0.0f, (float)500, 0.0f, (float)500);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, fontTexture);
        
        // Loop through the text and render each character
        for (const char *p = text; *p; p++) {
            // Fetch character data from baked font (cdata is the array of baked characters)
            stbtt_bakedchar c = cdata[*p - 32];
    
            // Calculate position for the character
            float xpos = x + c.xoff * scale;
            // Updated the ypos calculation to use c.yoff
            float ypos = y - c.yoff * scale;
    
            // Calculate the width and height from the bounding box
            float w = (c.x1 - c.x0) * scale; // Width of the character
            float h = (c.y1 - c.y0) * scale; // Height of the character
    
            // Define the vertices for the character quad
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
    
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };
    
            // Render the character quad
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
    
            // Draw the character
            glDrawArrays(GL_TRIANGLES, 0, 6);
    
            // Advance the cursor to the next character position
            x += (c.xadvance) * scale;
        }
    }

    void OpenGL::TriggerPostRedisplay()
    {
        glfwPostEmptyEvent();
    }
}
