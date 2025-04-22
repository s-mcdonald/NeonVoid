#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;

out vec3 vertexColor;

uniform mat4 modelMatrix;

void main()
{
    // Hardcode x, y positions directly
    float x = 0.0; // Hardcoded x-coordinate
    float y = 0.0; // Hardcoded y-coordinate

    gl_Position = modelMatrix * vec4(x, y, 0.0, 1.0); // Use hardcoded positions
    vertexColor = color;
}
