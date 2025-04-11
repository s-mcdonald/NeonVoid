
#include <iostream>

#include "glad/glad.h"   // Include glad first
#include <GLFW/glfw3.h>  // Include GLFW after glad

//
// NEXT !!!! KeyBoard Input
//
// https://learnopengl.com/Getting-started/Hello-Window
//

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height);
}

 int main()
 {
     glfwInit();
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

     GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL and Glad", nullptr, nullptr);
     if (window == nullptr)
     {
         std::cout << "Failed to create GLFW window" << std::endl;
         glfwTerminate();
         return -1;
     }
     glfwMakeContextCurrent(window);

     if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
     {
         std::cout << "Failed to initialize GLAD" << std::endl;
         return -1;
     }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.5f, 0.4f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
 }
