#version 330 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec4 iCol;
layout (location = 2) in vec2 iUV;

out vec4 oCol;
out vec2 oUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(iPos, 1.0);
    oCol = iCol;
    oUV = iUV;
}