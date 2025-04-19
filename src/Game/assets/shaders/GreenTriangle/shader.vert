#version 450 core

layout(location = 0) in vec2 position;

uniform mat4 modelMatrix;

void main() {
    gl_Position = modelMatrix * vec4(position, 0.0f, 1.0f);
}
