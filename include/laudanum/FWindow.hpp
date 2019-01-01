#ifndef _F_WINDOW_HPP
#define _F_WINDOW_HPP

#include "Fexcept.hpp"
#include "FInputListener.hpp"

#include <memory>

class GLFWwindow;

class FWindow {
    static std::size_t _instance_count;
    GLFWwindow* _window;

    FWindow(const FWindow&) = delete;
    FWindow(const FWindow&&) = delete;
public:

    // Initliaze based on GLFW window instance
    FWindow(GLFWwindow* window);

    // Underlying factory function that generates window instances
    // Create the GLFW window, in turn guarentees that any
    // instance of an FWindow mirrors an underlying GLFWwindow
    static std::unique_ptr<FWindow> create();

    // Pop and return any unhandled events on the queue
    bool getEvent(FInputEvent& input_event) noexcept;

    // Swap the buffer
    void draw() noexcept;

    // Destroy the underling GLFW instance
    // and uninitialize GLFW if possible
    ~FWindow();
};


#endif