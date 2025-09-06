#version 330 core

layout (location = 0) in vec3 iPos;

void main() {
    gl_Position = vec4(iPos.xyz, 1.0);
}