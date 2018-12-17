#include "laudanum/Fwindow.hpp"
#include "laudanum/Fexcept.hpp"
#include "laudanum/FDefines.hpp"

namespace FWindow {
    void glfwErrorCallback(int error_code, const char* description) {
        Flog("GLFW error %d:%s", error_code, description);
    }

    GLFWwindow* init() {

        // initialize GLFW
        glfwSetErrorCallback(glfwErrorCallback);

        if (!glfwInit()) {
            Flog("Could not initialize GLFW (used to create the window)");

            return nullptr;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // create the window to be fullscreen at the desktop resolution
        GLFWwindow* window;
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

        if (!vidmode) {
            Flog("Unable to get the primary monitor's video mode, using fallback resolution");

            window = glfwCreateWindow(FWINDOW_FALLBACK_W, FWINDOW_FALLBACK_W, FPROJECT_NAMEC, monitor, nullptr);
        } else {
            glfwWindowHint(GLFW_RED_BITS, vidmode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, vidmode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, vidmode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, vidmode->refreshRate);

            window = glfwCreateWindow(vidmode->width, vidmode->height, FPROJECT_NAMEC, monitor, nullptr);
        }

        if (!window) {
            Flog("Unable to create window, see related GLFW errors");

            glfwTerminate();

            return nullptr;
        }

        return window;
    }
}