/**
 * {SourceHeader}
 */

#pragma once

#include <vector>

#include <NeonRuntime/ExtRuntime.hpp>
#include <NeonEngine/AudioSystem.hpp>
#include <NeonEngine/Types.hpp>

namespace Neon
{
    class Entity;
    class Shader;
    class IVertexBuffer;

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
            virtual void OnInit() {};
            virtual void OnUpdate() {};
            virtual void OnRender() {};
            virtual void OnDestroy() {};

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
            void OnUpdate() override;
            void OnRender() override {};
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
            void HandleInput(Input* input); // keyboadInput ?

        public:
            void OnInit() override {};
            void OnUpdate() override;
            void OnRender() override {};
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
            explicit TextComponent(const std::string& text);
            ~TextComponent() override;

            [[nodiscard]] const std::string& GetText() const;
            void SetText(const std::string& text);

            [[nodiscard]] float GetFontSize() const;
            void SetFontSize(float fontSize);

            void OnInit() override;
            void OnUpdate() override;
            void OnRender() override {};

            [[nodiscard]] Point GetPosition() const;
            void OnDestroy() override;

        private:
            std::string m_text;
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
}
