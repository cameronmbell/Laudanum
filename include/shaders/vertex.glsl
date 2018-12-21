// By using a C++11 R string the shader comes packaged with the binary
// This shader runs on every input vertex

R""(
#version 330 core

layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)""