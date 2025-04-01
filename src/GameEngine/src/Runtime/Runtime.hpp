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
#include "AssetManager/AssetManager.hpp"

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


    class Component
    {
        public:
            Component() = default;
            virtual ~Component() = default;

        public:
            virtual void OnInit() {};
            virtual void OnUpdate() {};
            virtual void OnDestroy() {};
    };

    class QuadComponent final
        : public Component
    {
        public:
            QuadComponent();
            ~QuadComponent() override;

        public:
            void OnInit() override;
            void OnUpdate() override;
            void OnDestroy() override;

        private:  
            GLuint m_VAO;
            GLuint m_VBO;
            GLuint m_shaderProgram{};
            GLfloat m_vertices{};
    };

    class AudioComponent final
        : public Component
          , public AudioSystem
    {
        public:
            explicit AudioComponent(std::string filename);
            ~AudioComponent() override;

        public:
            void OnInit() override;
            void OnUpdate() override;

        public:
            void TriggerPlayOnce();
            void TriggerPlayRepeat();

        public:
            void SetVolume(const Volume& volume) override;
            void OnDestroy() override;

        private:
            std::string m_filename;    
            bool m_repeats;
    };

    class TextComponent final : public Component
    {
        public:
            explicit TextComponent(const std::string& text);
            TextComponent(const std::string& text, float fontSize);
            TextComponent(const std::string& text, float fontSize, const Point& point);
            TextComponent(std::string  text, float fontSize, const Point& point, ColorAlpha color);
            ~TextComponent() override;
    
        public:
            [[nodiscard]] const std::string& GetText() const;
            void SetText(const std::string& text);
    
            [[nodiscard]] float GetFontSize() const;
            void SetFontSize(float fontSize);

            void OnInit() override;
            void OnUpdate() override;

        public:
            [[nodiscard]] Point GetPosition() const;
            void OnDestroy() override;

        private:
            std::string m_text;
            float m_fontSize;
            Point m_point;
            ColorAlpha m_colorAlpha;
    };

    class PositionComponent final
        : public Component
    {
        public:
            explicit PositionComponent(float, float);
            void OnDestroy() override;

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
     class OpenGLRenderer final : public IRenderer
     {
        public:
            OpenGLRenderer();
            ~OpenGLRenderer() override;
        public:
            void BeginFrame() override;
            void EndFrame() override;
            void RenderText(const TextComponent& component) override;
            void RenderQuad(GLuint shaderProgram, GLuint VAO) override;

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

    class Scene
    {
        public:
            Scene() = delete;
            Scene(SceneType type, Platform* platform);
            virtual ~Scene();

        public:
            void Init();
            void Update();
            void Destroy();
            virtual void OnInit() {};
            virtual void OnUpdate() {};
            virtual void OnDestroy() {};
            bool IsInitialized() const;

        public:
            void AddComponent(const std::string& tag, Component* component);
            Component* GetComponent(const std::string& tag);

            SceneType GetSceneType() const;

        private:
            template <typename T>
            void InitRenderable(const T& t);

            template <typename T>
            void UpdateRenderable(const T& t);

            template <typename T>
            void DestroyRenderable(const T& t);

        protected:
            std::unordered_map<std::string, Entity*> m_entities;

        private:
            SceneType m_scene_type;
            Neon::Platform* m_platform{nullptr};
            bool m_isInitialized = false;
            std::unordered_map<std::string, Component*> m_components;
    };

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
            Scene* m_currentScene{nullptr};
    };

    class OpenGL final : public Platform
    {
        public:
            OpenGL();
            ~OpenGL() override;

            bool Initialize(int width, int height, const char* title) override;

            void Run(Game* game) override; 

            static GLuint CompileShader(const char* source, GLenum shaderType);
            static GLuint CreateShaderProgram(const char* vertexSource, const char* fragmentSource);

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
            bool Initialize(int width, int height, const char* title) const;
            void Run(Game* game) const;
            
            [[nodiscard]] Platform* GetPlatform() const;

        private:
            Platform* m_platform;
    };

    class GameEngineApi 
    {
        public:
            GameEngineApi(const GameEngineApi&) = delete;
            GameEngineApi& operator=(const GameEngineApi&) = delete;

        public:
            static GameEngineApi& getInstance();    
            static void RenderQuad(GLuint shaderProgram, GLuint VAO);
        
            [[nodiscard]] IRenderer* GetRenderer() const;

        private:
            GameEngineApi();
            ~GameEngineApi();

        private:
            IRenderer* m_renderer;
    };
}
 
