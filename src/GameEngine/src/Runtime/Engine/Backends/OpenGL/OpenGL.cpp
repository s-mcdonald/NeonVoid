/**
 * 
 */
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Runtime/Runtime.hpp>
#include <Runtime/Game.hpp>
#include <Runtime/Engine/Backends/OpenGL/OpenGL.hpp>
#include <Runtime/Engine/Backends/Container.hpp>
#include <Runtime/Engine/Backends/OpenGL/OpenGLInput.hpp>

void GLAPIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id,
                              GLenum severity, GLsizei length,
                              const GLchar* message, const void* userParam)
{
    std::cerr << "OpenGL Debug Message:" << std::endl;
    std::cerr << "---------------------" << std::endl;
    std::cerr << "Source: " << source << ", Type: " << type << std::endl;
    std::cerr << "Severity: " << severity << std::endl;
    std::cerr << "Message: " << message << std::endl;
    std::cerr << "---------------------" << std::endl;
}

void setupDebugOutput()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // Ensure errors are logged immediately
    glDebugMessageCallback(glDebugOutput, nullptr);
    // Optionally: Configure the severity of messages you want to listen for
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}

const char* getErrorString(GLenum error);

void checkErrors(const char* label)
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "OpenGL Error [" << label << "]: " << getErrorString(error) << std::endl;
    }
}

const char* getErrorString(GLenum error)
{
    switch (error) {
        case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
        case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
        case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
        case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        default: return "Unknown error";
    }
}

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

        //
        // Debugging..
        //
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); // Request a debug context

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

        // Debug only
        // if (glewIsSupported("GL_ARB_debug_output")) {
        //     std::cout << "GL_ARB_debug_output is supported!" << std::endl;
        // } else {
        //     std::cerr << "GL_ARB_debug_output is NOT supported on this system!" << std::endl;
        // }

        return true;
    }

    void OpenGL::Run(Game* game)
    {
        if (!m_window) return;

        if (!m_openGlInitialized) return;

        auto& container = Container::GetInstance();
        container.SetWindow(m_window);

        OpenGLKeyboardInput keyboardInput(m_window);

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

            // Poll and get events
            glfwPollEvents();

            // Handle input from user
            scene->HandleInput(&keyboardInput);

            // Update component/object data (now it also does render)
            scene->Update();

            // Do all Rendering here..

            glfwSwapBuffers(m_window);
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
