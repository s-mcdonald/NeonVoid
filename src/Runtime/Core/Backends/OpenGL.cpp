/**
 * 
 */
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

        // Initialize GLEW after setting the OpenGL context current
        if (glewInit() != GLEW_OK) {
            std::cerr << "Failed to initialize GLEW!" << std::endl;
            return false;
        }

        glViewport(0, 0, 800, 600);  // Set OpenGL viewport size

        std::cout << "OpenGL Initialized Successfully!\n";
        return true;
    }

    void OpenGL::Run(Game* game) 
    {
        if (!m_window) return;

        bool sceneInit = false;

        while (!glfwWindowShouldClose(m_window)) 
        {
            auto* scene = game->GetCurrentScene();
            if (sceneInit == false ) {
                scene->Init();
                sceneInit = true;
                std::cout << "Scene initialized in run loop\n";
            }

            // Check events like window close
            glfwPollEvents();

            scene->Render();

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

    void OpenGL::TriggerPostRedisplay()
    {
        glfwPostEmptyEvent();
    }

    GLuint OpenGL::compileShader(const char* source, GLenum shaderType) 
    {
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
    
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "Shader compilation failed: " << infoLog << std::endl;
        }
        return shader;
    }
    
    GLuint OpenGL::createShaderProgram(const char* vertexSource, const char* fragmentSource) 
    {
        GLuint vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
        GLuint fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);
    
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
    
        GLint success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cerr << "Program linking failed: " << infoLog << std::endl;
        }
    
        glDeleteShader(vertexShader);  // Cleanup after linking
        glDeleteShader(fragmentShader);
    
        return shaderProgram;
    }
    
}
