/**
 *    ███╗   ██╗███████╗ ██████╗ ███╗   ██╗
 *    ████╗  ██║██╔════╝██╔═══██╗████╗  ██║
 *    ██╔██╗ ██║█████╗  ██║   ██║██╔██╗ ██║
 *    ██║╚██╗██║██╔══╝  ██║   ██║██║╚██╗██║
 *    ██║ ╚████║███████╗╚██████╔╝██║ ╚████║
 *    ╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═══╝
 * ========================================
 *                 NeonVoid
 *         A 2D Game Engine in C++
 * ----------------------------------------
 * License: MIT
 * Copyright (c) : 2024 Sam McDonald
 * Repository: https://github.com/s-mcdonald/NeonVoid
 */

#include <cmath>
#include <iostream>

#include <NeonEngine/Application.hpp>

#include <NeonRuntime/Backends/OpenGL.hpp>
#include <NeonRuntime/Backends/OpenGLInput.hpp>
#include <NeonRuntime/Backends/OpenGLShader.hpp>
#include <NeonRuntime/Backends/OpenGLHeaders.hpp>
#include <NeonRuntime/Backends/OpenGLRenderer.hpp>

namespace Neon 
{
    OpenGL::~OpenGL()
    {
        if (m_window)
        {
            glfwDestroyWindow(m_window);
        }

        glfwTerminate();
    }

    bool OpenGL::Initialize(const int width, const int height, const char* title)
    {
        if (!glfwInit()) 
        {
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
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

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_DEPTH_TEST);

        // std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

        m_openGlInitialized = true;

        return true;
    }

    void OpenGL::Run(Application* application)
    {
        if (!m_window) return;

        if (!m_openGlInitialized) return;

        OpenGLKeyboardInput keyboardInput(m_window);

        while (!glfwWindowShouldClose(m_window))
        {
            OpenGLRenderer::BeginFrame(application->GetClearColor());

            auto* scene = application->GetCurrentScene();
            if (scene == nullptr)
            {
                glfwSetWindowShouldClose(m_window, true);
            }
            else
            {
                if (false == scene->IsInitialized())
                {
                    scene->Init();
                }

                glfwPollEvents();

                scene->HandleInput(&keyboardInput);
                scene->Render();
                scene->Update();

                glfwSwapBuffers(m_window);
            }

            OpenGLRenderer::EndFrame();
        }
        glfwTerminate();
    }

    IShader* OpenGL::CreateShader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        return new OpenGLShader(vertexPath, fragmentPath);
    }

    IVertexBuffer* OpenGL::CreateVertexBuffer(float* vertices, int* indices, size_t size)
    {
        return new OpenGLVertexBuffer(vertices, indices, size);
    }

    ITextBuffer* OpenGL::CreateTextBuffer(size_t bufferSize)
    {
        return new OpenGLTextBuffer();
    }
}
