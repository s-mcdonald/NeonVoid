/**
 * 
 */
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Runtime/OpenGL.h"

namespace Neon 
{
    Runtime::Runtime() : window(nullptr) 
    {
        // ...
    }

    Runtime::~Runtime() 
    {
        std::cout << "Runtime::Destructor called\n";
        CleanResources();
    }

    bool Runtime::Initialize(int width, int height, const char* title) 
    {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW!\n";
            return false;
        }

        // Create window
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window) {
            std::cerr << "Failed to create GLFW window!\n";
            glfwTerminate();
            return false;
        }

        // Set as the active window, without this it loads in background.
        glfwMakeContextCurrent(window);

        glfwSwapInterval(1);

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 

        std::cout << "OpenGL Initialized Successfully!\n";
        return true;
    }

    void Runtime::Run() 
    {
        if (!window) return;

        while (!glfwWindowShouldClose(window)) 
        {
            glfwPollEvents();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // perhaps the game has scene obj where we can get the current scene and render here.
            // game.GetCurrentScene().OnRender(); ??

            // Push to Ogl
            glfwSwapBuffers(window);
        }
    }

    void Runtime::CleanResources() 
    {
        if (window) 
        {
            glfwDestroyWindow(window);
        }
        glfwTerminate();
    }
}
