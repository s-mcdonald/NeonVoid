#version 450 core

layout (location = 0) in vec2 position;  // Changed from vec3 to vec2

uniform mat4 modelMatrix;

void main()
{
    gl_Position = modelMatrix * vec4(position.x, position.y, 0.0, 1.0);
}
