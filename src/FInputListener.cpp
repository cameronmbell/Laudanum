#include "laudanum/FInputListener.hpp"
#include "laudanum/FExcept.hpp"

#define _GLFW_PRESS_HELPER 1
#define _GLFW_RELEASE_HELPER 0

namespace FInputListener {

double _details::last_mouse_x = 0;
double _details::last_mouse_y = 0;
std::deque<FInputEvent> _details::event_queue;

void _details::pushKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action != _GLFW_PRESS_HELPER && action != _GLFW_RELEASE_HELPER) {
        FWarn("Unhandled key event for %d", key); 

        return;
    }

    _details::event_queue.push_back(FInputEvent { 
        /* type= */ (action == _GLFW_PRESS_HELPER) ? (FInputType::K_DOWN) : (FInputType::K_UP),
        {.mods=static_cast<FInputMod>(mods)},
        {.button=static_cast<FInputButton>(key)}
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
    if (action != _GLFW_PRESS_HELPER && action != _GLFW_RELEASE_HELPER) {
        FWarn("Unhandled mouse event for MB%d", button); 

        return;
    }

    _details::event_queue.push_back(FInputEvent { 
        /* type= */ (action == _GLFW_PRESS_HELPER) ? (FInputType::MB_DOWN) : (FInputType::MB_UP),
        {.mods=static_cast<FInputMod>(mods)},
        {.button=static_cast<FInputButton>(button)}
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