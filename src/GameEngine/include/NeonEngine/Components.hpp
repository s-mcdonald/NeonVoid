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
#include <chrono>

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
            Component(std::string tag) : m_tag(tag) {};
            virtual ~Component() = default;

            [[nodiscard]] Entity* GetParentEntity() const { return mx_entityParent; };
            void SetParentEntity(Entity* parent)
            {
                mx_entityParent = parent;
            }

            [[nodiscard]] Scene* GetScene() const { return mx_scene; };
            void SetScene(Scene* parent)
            {
                mx_scene = parent;
            }

            std::string GetTag() const
            {
                return m_tag;
            }

            virtual std::string GetType() const = 0;

            virtual void OnInit() {};
            virtual void OnUpdate() {};
            virtual void OnRender() {};
            virtual void OnDestroy()
            {
                mx_entityParent = nullptr;
                mx_scene = nullptr;
            };

        private:
            Entity* mx_entityParent = nullptr;
            Scene* mx_scene = nullptr;
            std::string m_tag;
    };

    class PositionComponent final : public Component
    {
        public:
            PositionComponent(const std::string& tag, Point p, float bounds = 1.0f)
                : Component(tag)
                , m_position(p.x, p.y)
                , m_bounds(bounds) {};
            ~PositionComponent() override
            {
                OnDestroy();
                Component::~Component();
            };

            std::string GetType() const override { return "position"; };

            void OnInit() override {};
            void OnUpdate() override {};
            void OnRender() override {};
            void OnDestroy() override
            {
                m_bounds = 0.0f;
            };

            [[nodiscard]] Point GetPoint() const { return m_position; };
            void SetPoint(Point p) { m_position = p; };
            [[nodiscard]] float GetBounds() const { return m_bounds; };

        private:
            Point m_position;
            float m_bounds;
    };

    class MovementComponent final : public Component
    {
        public:
            MovementComponent(const std::string& tag)
                : Component(tag)
                , m_velocity(0.0f, 0.0f)
                , m_directionInput(0.0f, 0.0f) {};
            ~MovementComponent() override
            {
                Component::OnDestroy();
            };

            std::string GetType() const override { return "movement"; };
            void HandleInput(Input* input);

            void OnInit() override {};
            void OnUpdate() override;
            void OnRender() override {};

        private:
            glm::vec2 m_velocity;
            glm::vec2 m_directionInput;
    };

    class AudioComponent final
        : public Component
    {
        public:
            explicit AudioComponent(const YComponent& audioData) :
                Component(audioData.name), m_repeats(false), m_volume(50)
            {
                m_filename = audioData.audioConfig->path;
                m_volume = Volume(audioData.audioConfig->volume);
            };
            ~AudioComponent() override
            {
                Component::~Component();
            };

            std::string GetType() const override { return "audio"; };

            void TriggerPlayOnce();
            void TriggerPlayRepeat();
            void SetVolume(const Volume&);

        private:
            AudioSystem audioSystem;
            std::string m_filename;
            bool m_repeats;
            Volume m_volume;
    };

    class TextComponent final : public Component
    {
        public:
            explicit TextComponent(const std::string& tag, std::string text, IShader* shader);
            ~TextComponent() override;

            std::string GetType() const override { return "text"; };

            void OnInit() override;
            void OnUpdate() override;
            void OnRender() override;
            void OnDestroy() override;

            void SetText(const std::string& text)
            {
                m_text = text;
            }

            void SetPosition(float x, float y);
            void SetVisible(bool visible);

        private:
            std::string m_text;
            IShader* m_shader;
            ITextBuffer* m_buffer{};
            float m_pos_x{0.0};
            float m_pos_y{0.0};
            bool m_visible{true};
    };

    class ShaderComponent final
        : public Component
    {
        public:
            ShaderComponent() = delete;
            explicit ShaderComponent(const std::string& tag, const std::vector<float>& vertices, const std::vector<int>& indicies, IShader* shader)
                : Component(tag)
                , m_shader(shader)
                , m_vertices(vertices)
                , m_indicies(indicies)
            {};
            ~ShaderComponent() override;

            std::string GetType() const override { return "shader"; };

            void OnInit() override;
            void OnUpdate() override;
            void OnRender() override {};
            void OnDestroy() override;

        private:
            IShader* m_shader;
            std::vector<float> m_vertices;
            std::vector<int> m_indicies;
            IVertexBuffer* m_buffer{};
            int m_verticesSize{};
    };

    class ScoreComponent final : public Component
    {
        public:
            ScoreComponent(const std::string& tag): Component(tag), m_score{0} {};
            ~ScoreComponent() override
            {
                Component::~Component();
            };

            std::string GetType() const override { return "score"; };

            Score GetScore() const
            {
                return m_score;
            }

            void AddScore(const Score value)
            {
                m_score += value;
            }

            void SubScore(const Score value)
            {
                m_score -= value;
            }

        private:
            Score m_score;
    };

    class HealthComponent final : public Component
    {
        public:
            HealthComponent(const std::string& tag): Component(tag), m_health{0} {};
            ~HealthComponent() override = default;

            std::string GetType() const override { return "health"; };

        public:
            [[nodiscard]] Score GetHealth() const;

        private:
            Health m_health;
    };

    class ScriptComponent final : public Component
    {
        public:
            explicit ScriptComponent(
                const std::string& tag,
                const std::function<void(Scene* scene)>& onUpdate, ScriptType type)
                : Component(tag)
                , m_scriptScene(onUpdate)
                , m_scriptEntity(nullptr)
                , m_scriptType(type)
            {}
            explicit ScriptComponent(const std::string& tag, const std::function<void(Entity* entity, Scene* scene)>& onUpdate, ScriptType type)
                : Component(tag)
                , m_scriptEntity(onUpdate)
                , m_scriptScene(nullptr)
                , m_scriptType(type)
            {}

            std::string GetType() const override { return "script"; };

            ~ScriptComponent() override
            {
                OnDestroy();
                Component::OnDestroy();
            };

            void OnInit() override
            {
                auto* _s = GetScene();

                if (_s == nullptr)
                {
                    return;
                }

                if (m_scriptType == ScriptType::SceneInit)
                {
                    m_scriptScene(_s);
                }
            }

            void OnUpdate() override
            {
                auto* _s = GetScene();

                if (_s == nullptr)
                {
                    return;
                }

                if (m_scriptType == ScriptType::EntityUpdate)
                {
                    auto* _e = GetParentEntity();

                    if (_e != nullptr && m_scriptEntity != nullptr)
                    {
                        m_scriptEntity(_e, _s);
                        return;
                    }
                }

                if (m_scriptType == ScriptType::SceneUpdate)
                {
                    m_scriptScene(_s);
                    return;
                }
            }

            void OnRender() override {}
            void OnDestroy() override
            {
                m_scriptScene = nullptr;
                m_scriptEntity = nullptr;
            }

        private:
            std::function<void(Scene* scene)> m_scriptScene;
            std::function<void(Entity* entity, Scene* scene)> m_scriptEntity;
            ScriptType m_scriptType;
    };

    class CollisionComponent final : public Component
    {
        public:
            CollisionComponent(const std::string& tag, float width, float height)
                : Component(tag)
                , m_width(width)
                , m_height(height) {}
            ~CollisionComponent() override
            {
                OnDestroy();
                Component::~Component();
            };

            std::string GetType() const override { return "collision"; };

            void OnDestroy() override
            {
                m_script = nullptr;
            };

            [[nodiscard]] float GetWidth() const { return m_width; }
            [[nodiscard]] float GetHeight() const { return m_height; }

            void OnCollision(const std::function<void(Entity* other)>& script)
            {
                m_script = script;
            };

            void OnCollision(Entity* other)
            {
                if (m_script != nullptr)
                {
                    m_script(other);
                }
            };

        private:
            float m_width;
            float m_height;
            std::function<void(Entity* other)> m_script{};
    };

    class TimerComponent final : public Component
    {
        public:
            TimerComponent(const std::string& tag, const std::function<void(Scene*)>& callback)
                : Component(tag)
                , m_delay(std::chrono::duration<float>(0.00))
                , m_callback(callback)
                , m_repeat(false)
                , m_running(false)
                , m_elapsedTime(0.0f)
            {
            }

            ~TimerComponent() override
            {
                Stop();
                m_callback = nullptr;
                Component::OnDestroy();
            };

            std::string GetType() const override { return "timer"; };

            void Start()
            {
                m_running = true;
                m_elapsedTime = 0.0f;
            }

            void Stop()
            {
                m_running = false;
            }

            bool IsRunning() const
            {
                return m_running;
            }

            float GetElapsedTime() const
            {
                return m_elapsedTime;
            }

            void OnInit() override
            {
                if (m_running)
                {
                    m_elapsedTime = 0.0f;
                }
            }

            void OnUpdate() override
            {
                if (!m_running)
                {
                    std::cout << "Timer not running" << std::endl;
                    return;
                }

                if (m_callback)
                {
                    auto* _s = GetScene();
                    m_callback(_s);

                    m_elapsedTime += deltaTime;
                }
            }

            void OnDestroy() override
            {
                Stop();
                m_callback = nullptr;
                Component::OnDestroy();
            }

        private:
            std::chrono::duration<float> m_delay;
            std::function<void(Scene*)> m_callback;
            bool m_repeat;
            bool m_running;
            float m_elapsedTime;
    };
}
