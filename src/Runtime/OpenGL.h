#pragma once

//#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Runtime/Core/Platform.h"

namespace Neon 
{
    class OpenGL : public Platform
    {
        public:
            OpenGL();
            ~OpenGL();

            bool Initialize(int width, int height, const char* title) override;

            void Run() override; 
 
        protected:
            void CleanResources() override;

        protected:
            GLFWwindow* m_window;
    };
}
