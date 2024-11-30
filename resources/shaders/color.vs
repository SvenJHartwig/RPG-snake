#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor; 

out vec3 vertexColor;

uniform mat4 uProjection;

void main() {
    gl_Position = uProjection * vec4(aPos, 0.0, 1.0);
    vertexColor = aColor;
}