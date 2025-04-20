/**
 * {SourceHeader}
 */

#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <NeonRuntime/Backends/OpenGLHeaders.hpp>
#include <NeonRuntime/Backends/OpenGLRenderer.hpp>

namespace Neon 
{
    void OpenGLRenderer::BeginFrame()
    {
        glClearColor(0.0f,0.0f,0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void OpenGLRenderer::EndFrame()
    {
        glFlush();
    }

    void OpenGLRenderer::RenderTriangle(const GLuint shaderProgram, const GLuint VAO, const GLsizei vertexCount)
    {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        GLint modelLoc = glGetUniformLocation(shaderProgram, "modelMatrix");

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        glBindVertexArray(0);
    }
}
