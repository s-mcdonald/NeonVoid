#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Neon 
{
    class OpenGL 
    {
        public:
            OpenGL();
            ~OpenGL();
    
            bool Initialize(int width, int height, const char* title);

            void Run();    
            
        protected:
            void CleanResources();

        private:
            GLFWwindow* window;
        };
}
