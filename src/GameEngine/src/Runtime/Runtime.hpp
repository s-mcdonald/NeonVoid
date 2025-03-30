/**
 *
 */

#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <unordered_map>
#include <deque>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <miniaudio.h>

#include "stb_truetype.h"

#include "Types.hpp"

#include "Audio/AudioSystem.hpp"
#include "Audio/Volume.hpp"
#include "Entity/Entity.hpp"

namespace Neon 
{
    class Game;

    using InitFunction = std::function<void()>;
    using RenderFunction = std::function<void()>;

    /******************************************** 
     *                                          *
     *           C O M P O N E N T S            *
     *                                          *
     ********************************************/

    class AssetManager
    {
        public:
            AssetManager();
            ~AssetManager();

        public:
            bool LoadTrueTypeFont(const char* fontPath);

        private:
            stbtt_fontinfo m_font;
            unsigned char* m_fontBuffer;
    };

    class IRenderable
    {
        //
    };

    class IComponent
    {
        public:
            virtual ~IComponent() = default;
            virtual void OnInit() = 0;
            virtual void OnUpdate() = 0;
    };

    class Component : public IComponent
    {
        public:
            Component();
            virtual ~Component();
        public:
            virtual void OnInit() override;
            virtual void OnUpdate() override;
    };

    class QuadComponent 
        : public Component
    {
        public:
            QuadComponent();
            ~QuadComponent();

        public:
            void OnInit();
            void OnUpdate();

        private:  
            GLuint m_VAO;
            GLuint m_VBO;
            GLuint m_shaderProgram;
            GLfloat m_vertices;
    };

    class AudioComponent 
        : public Component
        , public AudioSystem
    {
        public:
            AudioComponent(const std::string& filename);
            ~AudioComponent();

        public:
            void OnInit();
            void OnUpdate();

        public:
            void TriggerPlayOnce();
            void TriggerPlayRepeat();

        public:
            void SetVolume(const Volume& volume);

        private:
            std::string m_filename;    
            bool m_repeats;
    };

    class TextComponent : public Component, public IRenderable
    {
        public:
            TextComponent(const std::string& text);
            TextComponent(const std::string& text, float fontSize);
            TextComponent(const std::string& text, float fontSize, const Point& point);
            TextComponent(const std::string& text, float fontSize, const Point& point, ColorAlpha color);
            ~TextComponent();
    
        public:
            const std::string& GetText() const;
            void SetText(const std::string& text);
    
            float GetFontSize() const;
            void SetFontSize(float fontSize);

            void OnInit() override;
            void OnUpdate() override;

        public:
            Point GetPosition();
    
        private:
            std::string m_text;
            float m_fontSize;
            Point m_point;
            ColorAlpha m_colorAlpha;
    };

    class PositionComponent : public Component 
    {
        public:
            PositionComponent(float x = 0.0f, float y = 0.0f) : X(x), Y(y) {}
        
            // we should prob use Point for this
            float X, Y;
    };

    class ComponentManager 
    {
        public:
            template <typename T>
            void AddComponent(Entity& entity, T* component);
        
            template <typename T>
            T* GetComponent(const Entity& entity);
    };

    /******************************************** 
     *                                          *
     *          A P I    R E N D E R E R        *
     *                                          *
     ********************************************/

     class IRenderer
     {
        public:
            virtual ~IRenderer() = default;
        public:
            virtual void BeginFrame() = 0;
            virtual void EndFrame() = 0;
            virtual void RenderText(const TextComponent& component) = 0;
            virtual void RenderQuad(GLuint shaderProgram, GLuint VAO) = 0;
     };
 
     // we should make this static ?
     class OpenGLRenderer : public IRenderer
     {
        public:
            OpenGLRenderer();
            ~OpenGLRenderer() override;
        public:
            void BeginFrame() override;
            void EndFrame() override;
            void RenderText(const TextComponent& component) override;
            void RenderQuad(GLuint shaderProgram, GLuint VAO);

        private:

     };

#ifdef NEON_BUILD_VULKAN
    // todo: create a Vulkan renderer
    //  class VulkanRenderer : public IRenderer
    //  {
    //     public:
    //         VulkanRenderer() = default;
    //         ~VulkanRenderer() = default;
    //  };
#endif

    /******************************************** 
     *                                          *
     *          G A M E - C O N T R O L         *
     *                                          *
     ********************************************/

    class Platform 
    {
        public:
            Platform() = default;
            virtual ~Platform() = default;

        public:
            virtual bool Initialize(int width, int height, const char* title) = 0;
            virtual void Run(Game* game) = 0;
    };

    class Scene : public IComponent, public IRenderable
    {
        public:
            Scene() = delete;
            Scene(SceneType type, Platform* platform);
            ~Scene();

        public:
            void OnInit() override;
            void OnUpdate() override;
            bool IsInitialized() const;

        public:
            void AddComponent(const std::string& tag, Component* component);
            Component* GetComponent(const std::string& tag);
            SceneType GetSceneType() const;

        private:
            SceneType m_scene_type;
            Neon::Platform* m_platform{nullptr};
            bool m_isInitialized = false;
            std::unordered_map<std::string, Component*> m_components;
    };

    // define more scenes here... TitleScene ect

    class Game
    {
        public:
            Game();
            ~Game();

        public:
            void AddScene(Scene* scene);
            Scene* GetCurrentScene();
            void SwitchScene();

        private:
            std::deque<Scene*> m_scenes;
    };

    class OpenGL : public Platform
    {
        public:
            OpenGL();
            ~OpenGL();

            bool Initialize(int width, int height, const char* title) override;

            void Run(Game* game) override; 

            static GLuint CompileShader(const char* source, GLenum shaderType);
            static GLuint CreateShaderProgram(const char* vertexSource, const char* fragmentSource);

        protected:


        protected:
            GLFWwindow* m_window;
            bool m_openGlInitialized = false;

            AssetManager* m_assetManager;
    };

    class GameEngine
    {
        public:
            GameEngine();
            ~GameEngine();

        public:
            bool Initialize(int width, int height, const char* title);
            void Run(Game* game);
            
            Platform* GetPlatform() const;

        private:
            Platform* m_platform;
    };

    class GameEngineApi 
    {
        public:
            static GameEngineApi& getInstance();    
            static void RenderQuad(GLuint shaderProgram, GLuint VAO);
        
            IRenderer* GetRenderer();

        private:
            GameEngineApi();
            ~GameEngineApi();
        
            GameEngineApi(const GameEngineApi&) = delete;
            GameEngineApi& operator=(const GameEngineApi&) = delete;

        private:
            IRenderer* m_renderer;
    };
}
 
