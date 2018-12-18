#ifndef _F_INPUT_LISTENER_HPP
#define _F_INPUT_LISTENER_HPP

#include <deque>

class GLFWwindow;

enum class FInputType: int {
    UNKNOWN, // unnused, for future-proofing
    KEY_DOWN,
    KEY_UP,
    M_MOVE,
    MB_DOWN,
    MB_UP,
    WIN_CLOSE
};

struct FInputEvent {
    FInputType type;

    // The following agregate union definition is odd
    // because C++ lacks anonymous struct support
    // The members of the union used depend on when:
    //      type = KEY_DOWN, KEY_UP, MB_DOWN, MB_UP
    //      type = M_MOVE
    //      Otherwise no members are accessable (excluding type)
    // hence it simulates the following:
    // union {
    // struct { int mods;
    //          int button; };
    // struct{  double x, y; };
    //};
    union { double x; int mods; };
    union { double y; int button; };
};

class FWindow;

namespace FInputListener {
    namespace _details {
        extern double last_mouse_x;
        extern double last_mouse_y;
        extern std::deque<FInputEvent> event_queue;

        void pushKey(GLFWwindow* window, int key, int scancode, int action, int mods);
        void pushMouseMove(GLFWwindow* window, double xpos, double ypos);
        void pushMouseButton(GLFWwindow* window, int button, int action, int mods);
        void emplaceWindowClose(GLFWwindow* window);
    }

    bool pop(FInputEvent& event);
};

#endif