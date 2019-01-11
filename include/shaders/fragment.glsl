R""(#version 330 core

in vec2 fTexCoord;

uniform sampler2D texture0;

out vec4 oColor;

void main() {
    oColor = texture(texture0, fTexCoord);
})""

// By using a C++11 R string the shader comes packaged with the binary
// Hence a recompile is required after changing this file