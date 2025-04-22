/**
 *    ███╗   ██╗███████╗ ██████╗ ███╗   ██╗
 *    ████╗  ██║██╔════╝██╔═══██╗████╗  ██║
 *    ██╔██╗ ██║█████╗  ██║   ██║██╔██╗ ██║
 *    ██║╚██╗██║██╔══╝  ██║   ██║██║╚██╗██║
 *    ██║ ╚████║███████╗╚██████╔╝██║ ╚████║
 *    ╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═══╝
 * ========================================
 *                 NeonVoid
 *         A 2D Game Engine in C++
 * ----------------------------------------
 * License: MIT
 * Copyright (c) : 2024 Sam McDonald
 * Repository: https://github.com/s-mcdonald/NeonVoid
 */

#pragma once

#include <functional>
#include <iostream>
#include <ostream>
#include <vector>

#include <NeonEngine/Types.hpp>
#include <NeonEngine/AudioSystem.hpp>

#include <NeonRuntime/ExtRuntime.hpp>

namespace Neon
{
    class Scene;
    class Entity;

    class Component
    {
        public:
            Component() = default;
            virtual ~Component() = default;

            [[nodiscard]] Entity* GetParentEntity() const { return m_entityParent; };
            void SetParentEntity(Entity* parent)
            {
                m_entityParent = parent;
            }

            [[nodiscard]] Scene* GetScene() const { return m_scene; };
            void SetScene(Scene* parent)
            {
                m_scene = parent;
            }

        public:
            virtual void OnInit() {};
            virtual void OnUpdate() {};
            virtual void OnRender() {};
            virtual void OnDestroy() {};

        private:
            Entity* m_entityParent = nullptr;
            Scene* m_scene = nullptr;
    };

    class PositionComponent final : public Component
    {
        public:
            PositionComponent(Point p, float bounds = 1.0f)
                : Component()
                , m_position(p.x, p.y)
                , m_bounds(bounds) {};
            PositionComponent()
                : Component()
                , m_position(0.0f,0.0f)
                , m_bounds(1.0f){};
            explicit PositionComponent(const float x = 0.0f, const float y = 0.0f)
                : Component()
                , m_position(x,y)
                , m_bounds(1.0f){}
            ~PositionComponent() override = default;

        public:
            void OnInit() override {};
            void OnUpdate() override {};
            void OnRender() override {};
            void OnDestroy() override {};

        public:
            [[nodiscard]] Point GetPoint() const { return m_position; };

            // should we rename this to SetPoint ? hmm. I'll sit on it for now.
            void UpdateData(Point p) { m_position = p; };
            [[nodiscard]] float GetBounds() const { return m_bounds; };

        private:
            Point m_position;
            float m_bounds;
    };

    class MovementComponent final : public Component
    {
        public:
            MovementComponent()
                : Component()
                , m_velocity(0.0f, 0.0f)
                , m_directionInput(0.0f, 0.0f) {};
            ~MovementComponent() override = default;

            void HandleInput(Input* input);

            void OnInit() override {};
            void OnUpdate() override;
            void OnRender() override {};
            void OnDestroy() override {};

        private:
            glm::vec2 m_velocity;
            glm::vec2 m_directionInput;
    };

    class AudioComponent final
        : public Component
        , public AudioSystem
    {
        public:
            explicit AudioComponent(std::string filename)
                : Component()
                , AudioSystem()
                , m_filename(std::move(filename))
                , m_volume(50)
                , m_repeats(false) {};
            ~AudioComponent() override;

            void OnInit() override;
            void OnUpdate() override;
            void OnRender() override
            {
            };

            void TriggerPlayOnce();
            void TriggerPlayRepeat();
            void SetVolume(const Volume&) override;
            void OnDestroy() override;

        private:
            std::string m_filename;
            bool m_repeats;
            Volume m_volume;
    };

    class TextComponent final : public Component
    {
        public:
            explicit TextComponent(const std::string& text, IShader* shader);
            ~TextComponent() override;

            [[nodiscard]] const std::string& GetText() const;
            void SetText(const std::string& text);

            [[nodiscard]] float GetFontSize() const;
            void SetFontSize(float fontSize);

            void OnInit() override {};
            void OnUpdate() override;
            void OnRender() override {};

            [[nodiscard]] Point GetPosition() const;
            void OnDestroy() override {};

        private:
            std::string m_text;
            IShader* m_shader;
            IVertexBuffer* m_buffer{};
            float m_fontSize;
            Point m_point;
    };

    class ShaderComponent final
        : public Component
    {
        public:
            ShaderComponent() = delete;
            explicit ShaderComponent(const std::vector<float>& vertices, IShader* shader)
                : Component()
                , m_shader(shader)
                , m_vertices(vertices) {};
            ~ShaderComponent() override;

            void OnInit() override;
            void OnUpdate() override;
            void OnRender() override {};
            void OnDestroy() override;

            void UpdateData(const std::vector<float>& vertices);

        private:
            IShader* m_shader;
            std::vector<float> m_vertices;
            IVertexBuffer* m_buffer{};
            int m_verticesSize{};
    };

    class ScoreComponent final : public Component
    {
        public:
            ScoreComponent(): Component(), m_score{0} {};
            ~ScoreComponent() override = default;

        public:
            void OnInit() override {};
            void OnUpdate() override {};
            void OnRender() override {};
            void OnDestroy() override {};

        public:
            [[nodiscard]] Score GetScore() const;

        private:
            Score m_score;
    };

    class HealthComponent final : public Component
    {
        public:
            HealthComponent(): Component(), m_health{0} {};
            ~HealthComponent() override = default;

        public:
            void OnInit() override {};
            void OnUpdate() override {};
            void OnRender() override {};
            void OnDestroy() override {};

        public:
            [[nodiscard]] Score GetHealth() const;

        private:
            Health m_health;
    };

    class ScriptComponent final : public Component
    {
        public:
            explicit ScriptComponent(const std::function<void(Scene* scene)>& onUpdate)
                : Component()
                , m_scriptOnUpdateScene(onUpdate)
                , m_scriptOnUpdateEntity(nullptr)
                , m_isEntityScript(false)
            {}
            explicit ScriptComponent(const std::function<void(Entity* entity, Scene* scene)>& onUpdate)
                : Component()
                , m_scriptOnUpdateEntity(onUpdate)
                , m_scriptOnUpdateScene(nullptr)
                , m_isEntityScript(true)
            {}

            ~ScriptComponent() override
            {
                m_scriptOnUpdateScene = nullptr;
                m_scriptOnUpdateEntity = nullptr;
                m_isEntityScript = false;
            };

            void OnInit() override {}
            void OnUpdate() override
            {
                auto* _s = GetScene();
                auto* _e = GetParentEntity();

                if (_s == nullptr)
                {
                    return;
                }

                try
                {
                    if (m_isEntityScript)
                    {
                        if (_e != nullptr && m_scriptOnUpdateEntity != nullptr)
                        {
                            m_scriptOnUpdateEntity(_e, _s);
                        }
                    }
                    else
                    {
                        m_scriptOnUpdateScene(_s);
                    }
                }
                catch (const std::exception& e)
                {
                    std::cout << "Exception in script: " << e.what() << std::endl;
                }
                catch (...)
                {
                    std::cout << "Exception in script" << std::endl;
                }
            }

            void OnRender() override {}
            void OnDestroy() override {}

        private:
            std::function<void(Scene* scene)> m_scriptOnUpdateScene;
            std::function<void(Entity* entity, Scene* scene)> m_scriptOnUpdateEntity;
            bool m_isEntityScript;
    };

    class CollisionComponent final : public Component
    {
        public:
            CollisionComponent(float width, float height)
                : m_width(width)
                , m_height(height) {}
            ~CollisionComponent() override {};

            void OnInit() override {};
            void OnUpdate() override {};
            void OnRender() override {};
            void OnDestroy() override {};

            [[nodiscard]] float GetWidth() const { return m_width; }
            [[nodiscard]] float GetHeight() const { return m_height; }
            void OnCollision(Entity* other) {};

        private:
            float m_width;
            float m_height;
    };
}
