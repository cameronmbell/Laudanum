#ifndef _F_WINDOW_HPP
#define _F_WINDOW_HPP

#include "Fexcept.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace FWindow {
    GLFWwindow* init();
    void destroy(GLFWwindow* window);
};

#endif