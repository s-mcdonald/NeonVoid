#pragma once

#include <Runtime/Runtime.hpp>
#include <Runtime/Input/Input.hpp>

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

    class PositionComponent : public Component
    {
        public:
            explicit PositionComponent(float, float);
            void OnDestroy() override;
            [[nodiscard]] Point GetPoint() const;

        private:
            Point m_position;
    };

    class ControllerComponent : public Component
    {
        public:
            ControllerComponent() : Component() {};
            ~ControllerComponent() override = default;

        public:
            void HandleInput(const Input& input);
            void Update(float deltaTime);

        private:
            float m_velocityX = 0.0f;
            float m_velocityY = 0.0f;
            float m_accelerationX = 0.0f;
            float m_accelerationY = 0.0f;
            float m_maxSpeed = 500.0f;
            // rotation below
            float m_angle = 0.0f;
            float m_angularVelocity = 0.0f;
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
}
