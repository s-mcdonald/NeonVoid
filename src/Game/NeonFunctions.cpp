/**
 *
 */

#include <iostream>

#include "Runtime/Runtime.hpp"

#include "Game/NeonFunctions.hpp"

void Neon::LoadGameData(Game* game, GameEngine& gameEngine)
{
    using namespace Neon;
    {
        std::cout << "Entry ==> LoadGameData(game)\n";

        // Approved API
        // game->setTitleScene(scene, 10sec);
        // game->SetSceneSelectionMode(Mode::OnlySelectCurrentOrCompletedScenes, Mode::FreeSelectionViaMenu);

        // On Scene
        // scene->AddSoundTrack("playback.mp3");


        

        // Maybe a nice api fir title screens
        // This way the title scene is part of the GE and does not have to be manually coded
        // game->EnableTitleScene(true);

        // game->SetGameShortTitle("AstroVoid");
        // game->SetGameLongTitle("AstroVoid: Epic battle of Outter Space");
        // game->SetFont(FontNames::FontA)
        // game->SetFontSize(FontSizes::FontSize44)

        Scene* scene = new Scene(gameEngine.GetPlatform());

        // KeyBoardInput per scene, so each game level could have diff behaviour

        // the default game->kb controls are requried where the scene is optional
        // game->SetDefaultKeyboardControls(cb); // if a scene doesnt define, use these controls
        // scene->SetKeyboardControls(cb); // if there is no default

        game->AddScene(scene);

        Component* component = new Component();
        // We need a way to position a component especially if its visual, 
        // and move it around if need be. Have I done this right ??


        // OK, but now we have rendering on the component, but its OGL,
        // what should the dev do if he wants DX, ??
        // this I will have to think a bit more :(
        component->SetInitFunction([component]() {
            std::cout << "Initializing component...\n";

            // Define a simple triangle
            GLfloat vertices[] = {
                0.0f,  0.5f,    // Top vertex
                -0.5f, -0.5f,   // Bottom left
                0.5f, -0.5f     // Bottom right
            };

            // Generate m_VAO and m_VBO
            glGenVertexArrays(1, &component->m_VAO);
            glGenBuffers(1, &component->m_VBO);

            // Bind m_VAO and m_VBO
            glBindVertexArray(component->m_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, component->m_VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // Set the vertex attribute pointer
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(0);

            // Unbind m_VBO and m_VAO
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            // Compile and link shaders
            const char* vertexSource = R"(
                #version 330 core
                layout(location = 0) in vec2 position;
                void main() {
                    gl_Position = vec4(position, 0.0f, 1.0f);
                })";

            const char* fragmentSource = R"(
                #version 330 core
                out vec4 FragColor;
                void main() {
                    FragColor = vec4(0.4f, 0.7f, 0.2f, 1.0f);
                })";

            component->m_shaderProgram = OpenGL::CreateShaderProgram(vertexSource, fragmentSource);
        });
    
        component->SetRenderFunction([component]() {
            std::cout << "Rendering component...\n";

            glClear(GL_COLOR_BUFFER_BIT);
    
            glUseProgram(component->m_shaderProgram);  
        
            glBindVertexArray(component->m_VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);
        });       

        scene->AddComponent(component);
    }
}
