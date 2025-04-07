#pragma once

#include <Runtime/Runtime.hpp>

namespace Neon
{
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

        private:
            Shader* m_shader;
            std::vector<float> m_vertices;
            VertexBuffer* m_buffer{};
            int m_verticies_size{};
    };
}
