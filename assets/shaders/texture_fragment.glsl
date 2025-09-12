#version 330 core

in vec4 oCol;
in vec2 oUV;

out vec4 fragColor;

uniform sampler2D texture;

void main() {
    fragColor = texture2D(texture, oUV) * oCol;
}