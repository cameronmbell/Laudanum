#include "laudanum/FInputListener.hpp"
#include "laudanum/FExcept.hpp"

#include <GLFW/glfw3.h>

namespace FInputListener {

double _details::last_mouse_x = 0;
double _details::last_mouse_y = 0;
std::deque<FInputEvent> _details::event_queue;

void _details::pushKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS && action != GLFW_RELEASE) {
        FWarn("Unhandled key event for %d (%s)", key, glfwGetKeyName(key, scancode)); 

        return;
    }

    _details::event_queue.push_back(FInputEvent { 
        /* type= */ (action == GLFW_PRESS) ? (FInputType::KEY_DOWN) : (FInputType::KEY_UP),
        {.mods=mods},
        {.button=key}
     });
}

void _details::pushMouseMove(GLFWwindow* window, double xpos, double ypos) {
    _details::event_queue.push_back(FInputEvent {
        /* type= */ FInputType::M_MOVE,
        {.x=xpos},
        {.y=ypos}
    });

    _details::last_mouse_x = xpos;
    _details::last_mouse_y = ypos;
}

void _details::pushMouseButton(GLFWwindow* window, int button, int action, int mods) {
    if (action != GLFW_PRESS && action != GLFW_RELEASE) {
        FWarn("Unhandled mouse event for MB%d", button); 

        return;
    }

    _details::event_queue.push_back(FInputEvent { 
        /* type= */ (action == GLFW_PRESS) ? (FInputType::MB_DOWN) : (FInputType::MB_UP),
        {.mods=mods},
        {.button=button}
     });
}

// because window close is of higher importance than all other events
// it is pushed to the front of the queue
void _details::emplaceWindowClose(GLFWwindow* window) {
    _details::event_queue.push_front(FInputEvent {
        /* type= */ FInputType::WIN_CLOSE
    });
}

bool pop(FInputEvent& event) {
    if (_details::event_queue.empty())
        return false;

    event = _details::event_queue.front();
    _details::event_queue.pop_back();

    return true;
}

}