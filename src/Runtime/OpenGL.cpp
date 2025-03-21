/**
 * 
 */
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Runtime/OpenGL.h"
//#include "Runtime/Core/Platform.h"


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
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW!\n";
            return false;
        }

        // Create window
        m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!m_window) {
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
}
