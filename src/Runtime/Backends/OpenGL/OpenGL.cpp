/**
 * {SourceHeader}
 */

#include <cmath>
#include <iostream>

#include <NeonEngine/Application.hpp>
#include <NeonEngine/AssetManager/AssetManager.hpp>

#include <Runtime/Backends/OpenGL/OpenGL.hpp>
#include <Runtime/Backends/OpenGL/OpenGLInput.hpp>

namespace Neon 
{
    OpenGL::OpenGL()
        : IPlatform()
        , m_window(nullptr)
    {
        // not a good ref, since this points to GameEngine code, not runtime code.
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
        //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); // Request a debug context

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
            auto gameHeight = static_cast<int>(width / aspectRatio);

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

    void OpenGL::Run(Application* application)
    {
        if (!m_window) return;

        if (!m_openGlInitialized) return;

        OpenGLKeyboardInput keyboardInput(m_window);

        while (!glfwWindowShouldClose(m_window)) 
        {
            //Renderer::Clear();
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
            // glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
            //end: Renderer::Clear();

            auto* scene = application->GetCurrentScene();

            if (false == scene->IsInitialized())
            {
                scene->Init();
            }

            glfwPollEvents();

            scene->HandleInput(&keyboardInput);
            scene->Update();
            scene->Render();

            glfwSwapBuffers(m_window);
        }
    }

    ///
    /// Statics
    ///

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
