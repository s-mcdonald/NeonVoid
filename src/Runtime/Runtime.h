#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Neon 
{
    class Runtime 
    {
        public:
            Runtime();
            virtual ~Runtime();
    
            virtual bool Initialize(int width, int height, const char* title);

            virtual void Run();    
            
        protected:
            void CleanResources();

        protected:
            GLFWwindow* window;
        };
}
