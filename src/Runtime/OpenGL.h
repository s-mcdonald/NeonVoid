#pragma once

//#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Runtime/Core/Platform.h"
#include "Game/Game.h"

namespace Neon 
{
    class OpenGL : public Platform
    {
        public:
            OpenGL();
            ~OpenGL();

            bool Initialize(int width, int height, const char* title) override;

            void Run(Game* game) override; 
 
        protected:
            void CleanResources() override;

        protected:
            GLFWwindow* m_window;
    };
}
