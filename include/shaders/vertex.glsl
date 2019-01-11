R""(#version 330 core

layout (location = 0) in vec3 vVPos;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 uTransform;

out vec2 fTexCoord;

void main() {
    gl_Position = uTransform * vec4(vVPos, 1.0f);
    fTexCoord = vTexCoord;
})""

// By using a C++11 R string the shader comes packaged with the binary
// Hence a recompile is required after changing this file