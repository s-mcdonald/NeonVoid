/**
 * 
 */
#pragma once

namespace Neon 
{
    class Platform 
    {
        public:
            Platform();
            virtual ~Platform();
    
            virtual bool Initialize(int width, int height, const char* title);

            virtual void Run();    
            
        protected:
            virtual void CleanResources();
        };
}
