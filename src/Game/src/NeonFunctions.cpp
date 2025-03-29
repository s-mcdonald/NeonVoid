/**
 * Enhanced game data loading for Neon Void using the Neon game engine.
 * This version introduces a Renderer abstraction, enhanced components, UI elements,
 * scene transitions, and error handling.
 */

#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <memory>

#include "NeonFunctions.hpp"
#include "TitleScene.hpp"
#include "../../GameEngine/src/Runtime/Runtime.hpp"

// Forward declarations (assuming these are part of the engine)
namespace Neon {
    class Component;
    class AudioComponent;
    class TextComponent;
    class Scene;
    class Game;
    class GameEngine;
    class Platform;
    enum class SceneType { Title, Gameplay };
    struct Color { float r, g, b, a; Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f) : r(r), g(g), b(b), a(a) {} };
    struct Vector2 { float x, y; Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {} };
    namespace OpenGL {
        GLuint CreateShaderProgram(const char* vertexSource, const char* fragmentSource);
    }
}

// ### Renderer Class
// Abstracts OpenGL buffer and shader management for rendering.
class Renderer {
public:
    Renderer() {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set default background color
    }

    void CreateBuffer(const std::string& name, const std::vector<float>& vertices) {
        GLuint vao, vbo;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        buffers[name] = { vao, vbo };
    }

    void CreateShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) {
        GLuint program = Neon::OpenGL::CreateShaderProgram(vertexSource.c_str(), fragmentSource.c_str());
        shaders[name] = program;
    }

    void Render(const std::string& bufferName, const std::string& shaderName) {
        auto [vao, vbo] = buffers[bufferName];
        GLuint program = shaders[shaderName];
        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

private:
    std::map<std::string, std::pair<GLuint, GLuint>> buffers;
    std::map<std::string, GLuint> shaders;
};

// ### Enhanced AudioComponent
// Supports playback controls and volume adjustment.
class AudioComponent : public Neon::Component {
public:
    AudioComponent(const std::string& filePath) : filePath(filePath) {
        if (filePath.empty()) {
            std::cerr << "Error: Audio file path is empty\n";
        }
    }

    void Play() { std::cout << "Playing audio: " << filePath << "\n"; /* AudioSystem::Play(filePath); */ }
    void Pause() { std::cout << "Pausing audio: " << filePath << "\n"; /* AudioSystem::Pause(filePath); */ }
    void Stop() { std::cout << "Stopping audio: " << filePath << "\n"; /* AudioSystem::Stop(filePath); */ }
    void SetVolume(float volume) { 
        this->volume = volume; 
        std::cout << "Set volume to " << volume << " for " << filePath << "\n"; 
        /* AudioSystem::SetVolume(filePath, volume); */ 
    }

private:
    std::string filePath;
    float volume = 1.0f;
};

// ### Enhanced TextComponent
// Supports customizable text properties.
class TextComponent : public Neon::Component {
public:
    TextComponent(const std::string& text, int size, const std::string& font = "default", const Neon::Color& color = Neon::Color())
        : text(text), size(size), font(font), color(color) {}

    void SetText(const std::string& newText) { text = newText; }
    void SetColor(const Neon::Color& newColor) { color = newColor; }
    void Render() override { 
        std::cout << "Rendering text: " << text << " (Size: " << size << ", Font: " << font << ")\n"; 
        /* TextRenderer::DrawText(text, position, size, font, color); */ 
    }

private:
    std::string text;
    int size;
    std::string font;
    Neon::Color color;
    Neon::Vector2 position = Neon::Vector2(0.0f, 0.0f); // Default position
};

// ### ButtonComponent
// Adds UI interactivity with clickable actions.
class ButtonComponent : public Neon::Component {
public:
    ButtonComponent(const std::string& label, const std::function<void()>& onClick, Neon::Vector2 pos = Neon::Vector2(100.0f, 100.0f), Neon::Vector2 sz = Neon::Vector2(200.0f, 50.0f))
        : label(label), onClick(onClick), position(pos), size(sz) {}

    void Render() override { 
        std::cout << "Rendering button: " << label << " at (" << position.x << ", " << position.y << ")\n"; 
        /* UISystem::DrawButton(label, position, size); */ 
    }

    void OnMouseClick() { if (onClick) onClick(); }

private:
    std::string label;
    std::function<void()> onClick;
    Neon::Vector2 position;
    Neon::Vector2 size;
};

// ### GameplayScene
// A new scene type for gameplay content.
class GameplayScene : public Neon::Scene {
public:
    GameplayScene(Neon::SceneType type, Neon::Platform& platform) : Neon::Scene(type, platform) {}

    void Initialize() override {
        std::cout << "Initializing GameplayScene\n";
        // Add gameplay-specific components here in the future
    }
};

// ### LoadGameData Function
void Neon::LoadGameData(Game* game, GameEngine& gameEngine)
{
    using namespace Neon;
    {
        std::cout << "Entry ==> LoadGameData(game)\n";

        // Initialize Renderer
        Renderer renderer;

        // ### Title Scene Setup
        TitleScene* titleScene = new TitleScene(SceneType::Title, gameEngine.GetPlatform());
        game->AddScene(titleScene);

        // Triangle rendering component
        Component* triangleComponent = new Component();
        triangleComponent->SetInitFunction([triangleComponent, &renderer]() {
            std::cout << "Initializing triangle component...\n";
            std::vector<float> vertices = {
                0.0f,  0.5f,   // Top
                -0.5f, -0.5f,  // Bottom left
                0.5f, -0.5f    // Bottom right
            };
            renderer.CreateBuffer("triangle", vertices);

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
            renderer.CreateShader("basic", vertexSource, fragmentSource);
        });

        triangleComponent->SetRenderFunction([triangleComponent, &renderer]() {
            #if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
                std::cout << "Rendering triangle component...\n";
            #endif
            glClear(GL_COLOR_BUFFER_BIT);
            renderer.Render("triangle", "basic");
        });
        titleScene->AddComponent("render.triangle", triangleComponent);

        // Enhanced audio component
        AudioComponent* introMusic = new AudioComponent("./neon_void_intro.mp3");
        introMusic->SetVolume(0.8f);
        introMusic->Play();
        titleScene->AddComponent("aud.intro", introMusic);

        // Enhanced text component
        TextComponent* titleText = new TextComponent("Neon Void: A Saga", 24, "arial", Color(1.0f, 0.8f, 0.2f));
        titleScene->AddComponent("text.title", titleText);

        // Button to transition to gameplay scene
        ButtonComponent* startButton = new ButtonComponent("Start Game", [game]() {
            std::cout << "Transitioning to GameplayScene\n";
            // Placeholder: game->SetCurrentScene(SceneType::Gameplay);
        });
        titleScene->AddComponent("button.start", startButton);

        // ### Gameplay Scene Setup
        GameplayScene* gameplayScene = new GameplayScene(SceneType::Gameplay, gameEngine.GetPlatform());
        game->AddScene(gameplayScene);

        // Additional triangle in gameplay scene (example)
        Component* gameplayTriangle = new Component();
        gameplayTriangle->SetInitFunction([gameplayTriangle, &renderer]() {
            std::cout << "Initializing gameplay triangle...\n";
            std::vector<float> vertices = {
                0.0f,  0.3f,   // Top
                -0.3f, -0.3f,  // Bottom left
                0.3f, -0.3f    // Bottom right
            };
            renderer.CreateBuffer("gameplay_triangle", vertices);
            renderer.CreateShader("gameplay_shader", 
                "#version 330 core\nlayout(location = 0) in vec2 position;\nvoid main() { gl_Position = vec4(position, 0.0f, 1.0f); }",
                "#version 330 core\nout vec4 FragColor;\nvoid main() { FragColor = vec4(0.8f, 0.2f, 0.4f, 1.0f); }"
            );
        });
        gameplayTriangle->SetRenderFunction([gameplayTriangle, &renderer]() {
            glClear(GL_COLOR_BUFFER_BIT);
            renderer.Render("gameplay_triangle", "gameplay_shader");
        });
        gameplayScene->AddComponent("render.gameplay_triangle", gameplayTriangle);

        std::cout << "LoadGameData completed\n";
    }
}
