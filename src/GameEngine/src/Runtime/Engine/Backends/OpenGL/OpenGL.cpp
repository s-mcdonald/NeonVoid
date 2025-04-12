/**
 * 
 */
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Runtime/Runtime.hpp"
#include <Runtime/Game.hpp>
#include <Runtime/Engine/Backends/OpenGL/OpenGL.hpp>
#include <Runtime/Engine/Backends/Container.hpp>

namespace Neon 
{
    OpenGL::OpenGL() 
        : Platform()
        , m_window(nullptr)
    {
        m_assetManager = new AssetManager();
    }

    OpenGL::~OpenGL() 
    {
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
    bool OpenGL::Initialize(const int width, const int height, const char* title)
    {
        if (!glfwInit()) 
        {
            #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
                std::cerr << "Failed to initialize GLFW!\n";
            #endif
            
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
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

        glfwSetFramebufferSizeCallback(m_window, []( [[maybe_unused]]GLFWwindow* window, int width, int height)
        {
            float aspectRatio = 16.0f / 9.0f;

            int gameWidth = width;
            int gameHeight = static_cast<int>(width / aspectRatio);

            if (gameHeight > height)
            {
                gameHeight = height;
                gameWidth = static_cast<int>(height * aspectRatio);
            }

            const int viewportX = (width - gameWidth) / 2;
            const int viewportY = (height - gameHeight) / 2;

            glViewport(viewportX, viewportY, gameWidth, gameHeight);
        });

        m_openGlInitialized = true;

        return true;
    }

    void OpenGL::Run(Game* game)
    {
        if (!m_window) return;

        if (!m_openGlInitialized) return;

        auto container = Container::GetInstance();
        container.SetWindow(m_window);

        KeyboardInput keyboardInput(m_window);

        while (!glfwWindowShouldClose(m_window)) 
        {
            //Renderer::Clear();
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
            // glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
            //end: Renderer::Clear();

            auto* scene = game->GetCurrentScene();

            if (false == scene->IsInitialized())
            {
                scene->Init();
            }

            glfwPollEvents();

            scene->Update();

            glfwSwapBuffers(m_window);

            //KeyboardInput::
        }
    }

    ///
    /// Statics
    ///

    uint32_t OpenGL::CompileShader(const char* source, GLenum shaderType)
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
    
    uint32_t OpenGL::CreateShaderProgram(const char* vertexSource, const char* fragmentSource)
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

    std::vector<float> OpenGL::GenerateCircleVertices(const float radius, const int segments)
    {
        std::vector<float> vertices;

        vertices.push_back(0.0f); // X
        vertices.push_back(0.0f); // Y

        const float angleStep = 2.0f * M_PI / segments;

        for (auto i = 0; i <= segments; ++i)
        {
            const float angle = i * angleStep;
            vertices.push_back(std::cos(angle) * radius); // X
            vertices.push_back(std::sin(angle) * radius); // Y
        }

        return vertices;
    }
}
