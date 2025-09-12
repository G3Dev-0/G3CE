#version 330 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec4 iCol;
layout (location = 2) in vec2 iUV;

out vec4 oCol;
out vec2 oUV;

void main() {
    gl_Position = vec4(iPos.xyz, 1.0);
    oCol = iCol;
    oUV = iUV;
}