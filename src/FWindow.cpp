#include "laudanum/Fwindow.hpp"
#include "laudanum/Fexcept.hpp"
#include "laudanum/FDefines.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define FWINDOW_FALLBACK_W 1280
#define FWINDOW_FALLBACK_H 720

std::size_t FWindow::_instance_count = 0;

void glfwErrorCallback(int error_code, const char* description) {
    FErr("GLFW error (%d) %s", error_code, description);
}

// from make_unique and perfect forwarding by Herb Sutter
template<typename T, typename... Args>
std::unique_ptr<T> makeUnique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

std::unique_ptr<FWindow> FWindow::create() {

    // initialize GLFW
    glfwSetErrorCallback(glfwErrorCallback);

    if (FWindow::_instance_count < 1 && !glfwInit()) {
        FErr("Could not initialize GLFW (used to create the window)");

        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef FOS_APL
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // create the window to be fullscreen at the desktop resolution
    GLFWwindow* window;
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    if (!vidmode) {
        FWarn("Unable to get the primary monitor's video mode, using fallback resolution");

        window = glfwCreateWindow(FWINDOW_FALLBACK_W, FWINDOW_FALLBACK_W, FPROJECT_NAMEC, monitor, nullptr);
    } else {
        glfwWindowHint(GLFW_RED_BITS, vidmode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, vidmode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, vidmode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, vidmode->refreshRate);

        window = glfwCreateWindow(vidmode->width, vidmode->height, FPROJECT_NAMEC, monitor, nullptr);
    }

    if (!window) {
        FErr("Unable to create window. "
             "This is probaby because your GPU doesn't support OpenGL 3.3 "
             "Otherwise, see the related GLFW error");

        glfwTerminate();

        return nullptr;
    }

    // create OpenGL context on main thread
    glfwMakeContextCurrent(window);

    return makeUnique<FWindow>(window);
}

FWindow::FWindow(GLFWwindow* window) : _window(window) {
    _instance_count++;

    // repeat key events are OS specific and hence ignored
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_FALSE);

    // setup callbacks so the input listener can store events on a queue
    glfwSetKeyCallback(window, FInputListener::_details::pushKey);
    glfwSetCursorPosCallback(window, FInputListener::_details::pushMouseMove);
    glfwSetMouseButtonCallback(window, FInputListener::_details::pushMouseButton);
    glfwSetWindowCloseCallback(window, FInputListener::_details::emplaceWindowClose);
}

bool FWindow::getEvent(FInputEvent& input_event) {
    glfwPollEvents();

    return FInputListener::pop(input_event);
}

FWindow::~FWindow() {
    // don't check for nullptr on the _window object
    // this could potentially crash but speaks to the underlying philosphy
    // a crash for 1% of 1% of users is worth the reduced checking
    glfwDestroyWindow(_window);
    FWindow::_instance_count--;

    if (FWindow::_instance_count < 1)
        glfwTerminate();
}