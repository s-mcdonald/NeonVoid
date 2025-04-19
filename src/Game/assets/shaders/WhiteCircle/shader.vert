#version 450 core
layout(location = 0) in vec2 position;

void main() {
    float distance = length(position);
    if (distance > 1.0) {
        gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        gl_Position = vec4(position, 0.0, 1.0);
    }
}