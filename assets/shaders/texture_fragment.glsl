#version 330 core

in vec4 oCol;
in vec2 oUV;

out vec4 fragColor;

uniform bool debug_depth;
uniform sampler2D texture;

void main() {
    vec4 outputColor;
    if (debug_depth) {
        outputColor = vec4(vec3(gl_FragCoord.z), 1.0);
    } else {
        outputColor = texture2D(texture, oUV) * oCol;
    }
    fragColor = outputColor;
}