/**
 * {SourceHeader} // Assuming this is a placeholder for actual source file header info
 */

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // Required for glm::value_ptr

#include <Runtime/Runtime/Backends/Shader.hpp>
#include <Runtime/Components/Components.hpp> // Assuming PositionComponent is here
#include <Runtime/Runtime.hpp> // Assuming GameEngine is here
#include <Runtime/Runtime/Backends/OpenGL/GameEngineApi.hpp> // Assuming GameEngineApi and Renderer are here
#include <Runtime/Core/Base.hpp> // Assuming NEON_ASSERT is defined here
#include <Runtime/Core/Log.hpp> // Assuming logging macros like NEON_CORE_WARN, NEON_CORE_ERROR are here

#include <vector>
#include <string> // Added for uniform names
#include <cstddef> // For size_t
#include <memory> // Potentially for future smart pointer usage, good practice to include

// Debugging includes (conditionally compiled)
#ifdef NEON_DEBUG_KB_INPUT
#include <iostream>
#endif


namespace Neon
{
    // Forward declaration if Point struct is defined elsewhere, e.g., in PositionComponent.hpp
    // struct Point;

    // Constructor (Implied - Assuming one exists to initialize m_shader, m_vertices etc.)
    // ShaderComponent::ShaderComponent(Shader* shader, std::vector<float> vertices)
    //     : m_shader(shader), m_vertices(std::move(vertices)), m_buffer(nullptr)
    // {
    //     NEON_CORE_ASSERT(m_shader, "ShaderComponent created with null shader!");
    // }


    ShaderComponent::~ShaderComponent()
    {
        // Ensure cleanup is performed if not already explicitly called.
        // Note: Calling virtual functions from destructor has limitations,
        // but OnDestroy here seems intended for resource release before memory deletion.
        OnDestroy();

        // Delete the shader object itself (memory)
        // Ensure m_shader is not double-deleted if OnDestroy is called separately before destruction.
        // The check inside OnDestroy should prevent issues with m_shader->OnDelete(),
        // but the memory must be handled here.
        if (m_shader)
        {
            delete m_shader;
            m_shader = nullptr;
        }
        // Note: m_buffer is deleted within OnDestroy based on the original code's structure.
    }

    void ShaderComponent::OnInit()
    {
        NEON_CORE_ASSERT(m_shader, "Cannot initialize ShaderComponent: Shader is null!");
        NEON_CORE_ASSERT(!m_vertices.empty(), "Cannot initialize ShaderComponent: Vertex data is empty!");

        // Initialize the shader program (e.g., compile, link - happens inside m_shader->OnInit)
        if (m_shader) // Double check, although asserted above
        {
            m_shader->OnInit(); // Perform shader-specific initialization first
        }
        else
        {
             NEON_CORE_ERROR("ShaderComponent::OnInit - Shader pointer is null during initialization!");
             return; // Cannot proceed without a shader
        }

        // Create and setup the vertex buffer
        // Assuming GameEngine::CreateVertexBuffer returns nullptr on failure
        m_buffer = GameEngine::CreateVertexBuffer(m_vertices.data(), m_vertices.size() * sizeof(float));

        if (!m_buffer)
        {
            NEON_CORE_ERROR("ShaderComponent::OnInit - Failed to create Vertex Buffer!");
            // Optionally clean up shader if buffer creation fails? Depends on desired behavior.
            // if (m_shader) m_shader->OnDelete(); // Example cleanup
            return; // Cannot proceed without a buffer
        }

        // Bind/Unbind sequence often used to configure Vertex Array Object (VAO) state
        // associated with the buffer and shader attributes.
        m_buffer->Bind();
        // TODO: Set up Vertex Attributes here using m_shader attribute locations and m_buffer layout
        // Example:
        // m_shader->Bind(); // Bind shader to set attributes
        // GLuint positionAttribLocation = glGetAttribLocation(m_shader->GetShaderProgramId(), "aPos");
        // if (positionAttribLocation != -1) {
        //    glVertexAttribPointer(positionAttribLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        //    glEnableVertexAttribArray(positionAttribLocation);
        // } else {
        //    NEON_CORE_WARN("ShaderComponent::OnInit - Attribute 'aPos' not found in shader.");
        // }
        // // Add other attributes (color, texcoords) if needed
        m_buffer->Unbind();
        // m_shader->Unbind(); // Unbind shader if bound for attribute setup

        NEON_CORE_INFO("ShaderComponent Initialized successfully.");
    }

    void ShaderComponent::OnUpdate()
    {
        // Ensure component is ready
        if (!m_shader || !m_buffer)
        {
            NEON_CORE_WARN("ShaderComponent::OnUpdate - Skipping update, component not fully initialized (shader or buffer missing).");
            return;
        }

        // --- Get Position from Parent Entity ---
        glm::vec3 position(0.0f); // Use glm::vec3 for consistency with matrix operations
        Entity* parent = GetParentEntity(); // Assuming IComponent has GetParentEntity()

        if (parent != nullptr && parent->HasComponent<PositionComponent>())
        {
            // Use const auto* for safety if we don't intend to modify the PositionComponent here
            const auto* posComp = parent->GetComponent<PositionComponent>();
            if (posComp) // Check if GetComponent returned a valid pointer
            {
                Point p = posComp->GetPoint(); // Assuming GetPoint returns the Point struct
                position.x = p.x;
                position.y = p.y;
                position.z = 0.0f; // Assuming 2D, Z is 0

                #ifdef NEON_DEBUG_KB_INPUT
                    // Using NEON logging macros is generally preferred over std::cout
                    NEON_CORE_TRACE("[DEBUG](Shader) Parent Position: x={}, y={}", position.x, position.y);
                #endif
            }
            else
            {
                 NEON_CORE_WARN("ShaderComponent::OnUpdate - Parent has PositionComponent but GetComponent returned null!");
            }
        }
        // If no parent or no PositionComponent, position remains (0,0,0)


        // --- Prepare for Rendering ---
        const auto& api = GameEngineApi::getInstance(); // Assuming this is a valid way to get the API/Renderer
        auto* renderer = api.GetRenderer();
        if (!renderer) {
            NEON_CORE_ERROR("ShaderComponent::OnUpdate - Failed to get Renderer from GameEngineApi!");
            return;
        }

        // --- Bind Resources ---
        m_shader->Bind(); // Bind the shader program for this component
        m_buffer->Bind(); // Bind the VAO/VBO for this component

        // --- Calculate Model Matrix ---
        glm::mat4 modelMatrix = glm::mat4(1.0f); // Start with identity matrix
        // Apply translation based on the fetched position
        modelMatrix = glm::translate(modelMatrix, position);
        // Apply other transformations if needed (rotation, scale)
        // modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));
        // modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleFactor, scaleFactor, 1.0f));


        // --- Set Uniforms ---
        // Use shader class method if available (preferred)
        if (!m_shader->SetUniformMat4fv("u_ModelMatrix", modelMatrix)) // Use a consistent naming convention like u_
        {
             NEON_CORE_WARN("ShaderComponent::OnUpdate - Failed to set 'u_ModelMatrix' uniform. Is it defined in the shader?");
             // Fallback to raw OpenGL calls if necessary and the Shader class provides access
             // GLint uniformLoc = glGetUniformLocation(m_shader->GetShaderProgramId(), "u_ModelMatrix");
             // if (uniformLoc != -1) {
             //     glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
             // } else {
             //     NEON_CORE_WARN("ShaderComponent::OnUpdate - Uniform 'u_ModelMatrix' not found using glGetUniformLocation.");
             // }
        }

        // Set other uniforms (View, Projection matrices - likely set globally or by a CameraComponent)
        // m_shader->SetUniformMat4fv("u_ViewMatrix", viewMatrix);
        // m_shader->SetUniformMat4fv("u_ProjectionMatrix", projectionMatrix);
        // m_shader->SetUniformVec4f("u_Color", color);


        // --- Render ---
        // The number of vertices to render should be based on the original vertex data size,
        // divided by the number of components per vertex (e.g., 2 for vec2 positions).
        // Assuming m_vertices stores pairs of floats (x, y).
        size_t vertexCount = m_vertices.size() / 2; // Calculate number of vertices

        // Check if RenderCircle expects number of floats or number of vertices
        // Assuming it expects the number of *vertices* to draw. Adjust if it expects number of floats.
        renderer->RenderCircle(m_shader->GetShaderProgramId(), m_buffer->GetVao(), vertexCount); // Pass VAO ID and vertex count

        // --- Unbind Resources ---
        m_buffer->Unbind(); // Unbind VAO/VBO
        m_shader->Unbind(); // Unbind shader program
    }

    /**
     * @brief Updates the vertex buffer data on the GPU.
     * @param vertices The new vertex data (e.g., positions, colors).
     * @note This replaces the entire buffer content. It does NOT modify the component's internal m_vertices copy.
     * Use this if the base shape/data needs to change, not just for transformations (use uniforms for that).
     */
    void ShaderComponent::UpdateData(const std::vector<float>& newVertices)
    {
        // Check if buffer exists and if new data is provided
        if (!m_buffer) {
             NEON_CORE_ERROR("ShaderComponent::UpdateData - Cannot update data, vertex buffer is null!");
             return;
        }
        if (newVertices.empty()) {
             NEON_CORE_WARN("ShaderComponent::UpdateData - Attempted to update with empty vertex data.");
             // Optionally clear the buffer or just return
             // m_buffer->UpdateData(nullptr, 0); // Clear buffer if supported
             return;
        }

        // Update the GPU buffer, but NOT the internal m_vertices member.
        // The internal m_vertices should generally hold the "base" vertex data.
        m_buffer->UpdateData(newVertices.data(), newVertices.size() * sizeof(float));

        // If the intent IS to also update the internal copy (e.g. the base shape changed permanently):
        // this->m_vertices = newVertices;
        // NEON_CORE_INFO("ShaderComponent::UpdateData - Updated vertex buffer and internal vertex copy.");
        // Be cautious with this, as the size might change, affecting rendering counts.
    }

    /**
     * @brief Cleans up GPU resources associated with the component.
     * Should be called before the component object is destroyed.
     * Note: This is called automatically by the destructor for basic cleanup.
     */
    void ShaderComponent::OnDestroy()
    {
        NEON_CORE_INFO("ShaderComponent::OnDestroy - Cleaning up resources...");

        // Cleanup Shader resources (GPU program)
        if (m_shader)
        {
            // Unbind shader if it happens to be bound (good practice)
            // Note: In a well-structured engine, binding state should be managed per draw call.
             m_shader->Unbind(); // Safe to call even if not bound

            // Delete the GPU shader program object
             m_shader->OnDelete();
            // Do NOT delete m_shader pointer here, memory is handled by destructor.
        }

        // Cleanup Buffer resources (VBO/VAO)
        if (m_buffer)
        {
             // Buffer deletion might implicitly handle unbinding, but explicit unbind is safer if needed elsewhere.
             // m_buffer->Unbind(); // Optional: Ensure unbinding before deletion if necessary

            // Delete the VBO/VAO (GPU resources and potentially CPU memory wrapper)
             delete m_buffer;
             m_buffer = nullptr; // Set pointer to null after deletion
        }
        else
        {
             NEON_CORE_WARN("ShaderComponent::OnDestroy - Buffer was already null.");
        }
    }

} // namespace Neon
