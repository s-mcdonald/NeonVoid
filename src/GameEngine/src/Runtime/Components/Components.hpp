#pragma once

#include "Runtime/Scene/Scene.hpp"


#include <Runtime/Runtime.hpp>
#include <Runtime/Runtime/Input.hpp>

namespace Neon
{
    class Entity;
    class Shader;
    class VertexBuffer;

    class Component
    {
        public:
            Component() = default;
            virtual ~Component() = default;

        public:
            [[nodiscard]] Entity* GetParentEntity() const { return m_entityParent; };
            void SetParentEntity(Entity* parent)
            {
                m_entityParent = parent;
            }

        public:
            virtual void OnInit() = 0;
            virtual void OnUpdate() = 0;
            virtual void OnDestroy() = 0;

        private:
            Entity* m_entityParent = nullptr;
    };

    class PositionComponent final : public Component
    {
        public:
            PositionComponent()
                : Component()
                , m_position(0.0f,0.0f) {};
            explicit PositionComponent(float, float);
            ~PositionComponent() override = default;

        public:
            void OnInit() override {};
            void OnUpdate() override {};
            void OnDestroy() override;

        public:
            [[nodiscard]] Point GetPoint() const;
            void UpdateData(Point p);

        private:
            Point m_position;
    };

    class MovementComponent : public Component
    {
        public:
            MovementComponent() : Component()
            {
                // ...
            };

            ~MovementComponent() override
            {
                // ...
            }

        public:
            void AllowMovementOf(PositionComponent* component);
            void HandleInput(OpenGLInput* input);

        public:
            void OnInit() override {};
            void OnUpdate() override;
            void OnDestroy() override {};

        private:
            std::vector<PositionComponent*> mx_positionalComponents;
            float m_directionX = 0.0f;
            float m_directionY = 0.0f;
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
                , m_repeats(false) {};
            ~AudioComponent() override = default;

            void OnInit() override;
            void OnUpdate() override;
            void TriggerPlayOnce();
            void TriggerPlayRepeat();
            void SetVolume(const Volume&) override;
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

            [[nodiscard]] const std::string& GetText() const;
            void SetText(const std::string& text);

            [[nodiscard]] float GetFontSize() const;
            void SetFontSize(float fontSize);

            void OnInit() override;
            void OnUpdate() override;

            [[nodiscard]] Point GetPosition() const;
            void OnDestroy() override;

        private:
            std::string m_text;
            float m_fontSize;
            Point m_point;
            ColorAlpha m_colorAlpha;
    };

    class ShaderComponent final
        : public Component
    {
        public:
            ShaderComponent() = delete;
            explicit ShaderComponent(const std::vector<float>& vertices, Shader* shader)
                : Component()
                , m_shader(shader)
                , m_vertices(vertices) {};
            ~ShaderComponent() override;

            void OnInit() override;
            void OnUpdate() override;
            void OnDestroy() override;

            void UpdateData(const std::vector<float>& vertices);

        private:
            Shader* m_shader;
            std::vector<float> m_vertices;
            VertexBuffer* m_buffer{};
            int m_verticiesSize{};
    };

    class ScoreComponent final : public Component
    {
        public:
            ScoreComponent(): Component(), m_score{0} {};
            ~ScoreComponent() override = default;

        public:
            void OnInit() override {};
            void OnUpdate() override {};
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
            void OnDestroy() override {};

        public:
            [[nodiscard]] Score GetHealth() const;

        private:
            Health m_health;
    };
}
