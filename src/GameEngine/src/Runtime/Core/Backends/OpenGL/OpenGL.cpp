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
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "OpenGL::Constructor called\n";
        #endif

        m_assetManager = new AssetManager();
    }

    OpenGL::~OpenGL() 
    {
        #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
            std::cout << "OpenGL::Destructor called\n";
        #endif

        delete m_assetManager;

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
            #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
                std::cerr << "Failed to initialize GLFW!\n";
            #endif
            
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

        if (glewInit() != GLEW_OK) 
        {
            std::cerr << "Failed to initialize GLEW!" << std::endl;
            return false;
        }

        // just remember the wxh here is not always the same as window wxh
        glViewport(0, 0, width, height);  // Set OpenGL viewport size

        std::cout << "OpenGL Initialized Successfully!\n";

        m_openGlInitialized = true;

        //
        // Assets
        // Attempt to load assets, font textures ect here..
        //
        m_assetManager->LoadTrueTypeFont("./assets/fonts/default.ttf");

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

            glClear(GL_COLOR_BUFFER_BIT);

            // Check events like window close
            glfwPollEvents();

            scene->OnUpdate();

            glfwSwapBuffers(m_window);
        }
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
        if (!success) 
        {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);

            #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
                std::cerr << "Shader compilation failed: " << infoLog << std::endl;
            #endif
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
        if (!success) 
        {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
                std::cerr << "Program linking failed: " << infoLog << std::endl;
            #endif
        }
    
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    
        return shaderProgram;
    }
}
