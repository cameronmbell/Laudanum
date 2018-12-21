// By using a C++11 R string the shader comes packaged with the binary
// This shader runs on every output pixel

R""(
#version 330 core

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 
)""