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

        public:
            virtual void OnInit() {};
            virtual void OnUpdate() {};
            virtual void OnRender() {};
            virtual void OnDestroy() {};

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
            explicit PositionComponent(const std::string& tag, const float x = 0.0f, const float y = 0.0f)
                : Component(tag)
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
            MovementComponent(const std::string& tag)
                : Component(tag)
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
            explicit AudioComponent(const std::string& tag, std::string filename)
                : Component(tag)
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
            explicit TextComponent(const std::string& tag, std::string text, IShader* shader);
            ~TextComponent() override;

            void OnInit() override;
            void OnUpdate() override;
            void OnRender() override;
            void OnDestroy() override;

        private:
            std::string m_text;
            IShader* m_shader;
            ITextBuffer* m_buffer{};
    };

    class ShaderComponent final
        : public Component
    {
        public:
            ShaderComponent() = delete;
            explicit ShaderComponent(const std::string& tag, const std::vector<float>& vertices, IShader* shader)
                : Component(tag)
                , m_shader(shader)
                , m_vertices(vertices) {};
            ~ShaderComponent() override;

            void OnInit() override;
            void OnUpdate() override;
            void OnRender() override {};
            void OnDestroy() override;

        private:
            IShader* m_shader;
            std::vector<float> m_vertices;
            IVertexBuffer* m_buffer{};
            int m_verticesSize{};
    };

    class ScoreComponent final : public Component
    {
        public:
            ScoreComponent(const std::string& tag): Component(tag), m_score{0} {};
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
            HealthComponent(const std::string& tag): Component(tag), m_health{0} {};
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

            ~ScriptComponent() override
            {
                m_scriptScene = nullptr;
                m_scriptEntity = nullptr;
            };

            void OnInit() override
            {
                auto* _s = GetScene();

                if (_s == nullptr)
                {
                    return;
                }

                try
                {
                    if (m_scriptType == ScriptType::SceneInit)
                    {
                        m_scriptScene(_s);
                    }
                }
                catch (const std::exception& e)
                {
                    std::cout << "Exception in OnInit::Script: " << e.what() << std::endl;
                }
                catch (...)
                {
                    std::cout << "Exception in OnInit::Script" << std::endl;
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
                    }
                }

                if (m_scriptType == ScriptType::SceneUpdate)
                {
                    m_scriptScene(_s);
                }
            }

            void OnRender() override {}
            void OnDestroy() override {}

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
            ~CollisionComponent() override {};

            void OnInit() override {};
            void OnUpdate() override {};
            void OnRender() override {};
            void OnDestroy() override {};

            [[nodiscard]] float GetWidth() const { return m_width; }
            [[nodiscard]] float GetHeight() const { return m_height; }

            void OnCollision(Entity* other)
            {
                std::cout << "Collision detected" << std::endl;

                // perhaps we can call a user script.
                // or a script can be part of a collision?
            };

        private:
            float m_width;
            float m_height;
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

            ~TimerComponent() override = default;

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

            void SetRepeat(bool repeat)
            {
                m_repeat = repeat;
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
            }

        private:
            std::chrono::duration<float> m_delay;
            std::function<void(Scene*)> m_callback;
            bool m_repeat;
            bool m_running;
            float m_elapsedTime;
    };
}
