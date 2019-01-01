// By using a C++11 R string the shader comes packaged with the binary
// Hence a recompile is required after changing this file

R""(
#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;

out vec3 vCol;

uniform float time;

void main() {
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0) + 0.1 * time;
    vCol = col;
}
)""