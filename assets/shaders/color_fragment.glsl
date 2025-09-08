#version 330 core

in vec4 oCol;

out vec4 fragColor;

void main() {
    fragColor = vec4(oCol.rgb, 1);
}