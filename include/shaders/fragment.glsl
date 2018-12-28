// By using a C++11 R string the shader comes packaged with the binary
// Hence a recompile is required after changing this file

R""(
#version 330 core

out vec4 FragColor;

void main() {
    FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
} 
)""