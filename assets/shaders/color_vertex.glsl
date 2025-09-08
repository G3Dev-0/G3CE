#version 330 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec4 iCol;

out vec4 oCol;

void main() {
    oCol = iCol;
    gl_Position = vec4(iPos.xyz, 1.0);
}