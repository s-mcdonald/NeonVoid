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

        if (m_window) 
        {
            glfwDestroyWindow(m_window);
        }
        glfwTerminate();
    }

    ///
    /// Initialize OpenGL core before render
    ///
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

        m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!m_window) 
        {
            std::cerr << "Failed to create GLFW window!\n";
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(m_window);

        if (glewInit() != GLEW_OK) {
            std::cerr << "Failed to initialize GLEW!" << std::endl;
            return false;
        }

        // just remember the wxh here is not always the same as window wxh
        glViewport(0, 0, width, height);  // Set OpenGL viewport size

        std::cout << "OpenGL Initialized Successfully!\n";

        m_openGlInitialized = true;

        return true;
    }

    void OpenGL::Run(Game* game) 
    {
        if (!m_window) return;

        if (!m_openGlInitialized) return;

        while (!glfwWindowShouldClose(m_window)) 
        {
            auto* scene = game->GetCurrentScene();

            if (false == scene->IsInitialized())
            {
                scene->OnInit();
                std::cout << "Scene initialized in run loop\n";
            }

            // Check events like window close
            glfwPollEvents();

            scene->OnUpdate();

            glfwSwapBuffers(m_window);
        }
    }

    void OpenGL::TriggerPostRedisplay()
    {
        glfwPostEmptyEvent();
    }
    
    ///
    /// Statics
    ///

    GLuint OpenGL::CompileShader(const char* source, GLenum shaderType) 
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
    
    GLuint OpenGL::CreateShaderProgram(const char* vertexSource, const char* fragmentSource) 
    {
        GLuint vertexShader = OpenGL::CompileShader(vertexSource, GL_VERTEX_SHADER);
        GLuint fragmentShader = OpenGL::CompileShader(fragmentSource, GL_FRAGMENT_SHADER);
    
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
