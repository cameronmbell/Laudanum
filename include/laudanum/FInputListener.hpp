#ifndef _F_INPUT_LISTENER_HPP
#define _F_INPUT_LISTENER_HPP

#include <deque>

class GLFWwindow;

// Represents the type of event that occured and subsequently
// the payload it carries
enum class FInputType: int;

// Which mouse/keyboard button was pressed?
// Can implicitly convert to GLFW key code
enum class FInputButton : int;

// The modifier bits for a button press
// Can implicitly convert to GLFW mods
enum class FInputMod : int;

// Because mods work through bit toggling, convert it to a bool
// E.g. FINPUT_HAS_MOD(event.mods, FInputMod::SHIFT)
#define FINPUT_HAS_MOD(_bits, _mod) !!(static_cast<int>((_bits)) & static_cast<int>((_mod)))

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
    union { double x; FInputMod mods; };
    union { double y; FInputButton button; };
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

enum class FInputType: int {
    UNKNOWN, // unnused, for future-proofing
    K_DOWN,
    K_UP,
    M_MOVE,
    MB_DOWN,
    MB_UP,
    WIN_CLOSE
};

enum class FInputButton: int {
    MB_1=0,
    MB_2=1,
    MB_3=2,
    MB_4=3,
    MB_5=4,
    MB_6=5,
    MB_7=6,
    MB_8=7,
    MB_LAST=7,
    MB_LEFT=0,
    MB_RIGHT=1,
    MB_MIDDLE=2,

    K_UNKNOWN=-1,

    K_SPACE=32,
    K_APOSTROPHE=39,
    K_COMMA=44,
    K_MINUS=45,
    K_PERIOD=46,
    K_SLASH=47,
    K_0=48,
    K_1=49,
    K_2=50,
    K_3=51,
    K_4=52,
    K_5=53,
    K_6=54,
    K_7=55,
    K_8=56,
    K_9=57,
    K_SEMICOLON=59,
    K_EQUAL=61,
    K_A=65,
    K_B=66,
    K_C=67,
    K_D=68,
    K_E=69,
    K_F=70,
    K_G=71,
    K_H=72,
    K_I=73,
    K_J=74,
    K_K=75,
    K_L=76,
    K_M=77,
    K_N=78,
    K_O=79,
    K_P=80,
    K_Q=81,
    K_R=82,
    K_S=83,
    K_T=84,
    K_U=85,
    K_V=86,
    K_W=87,
    K_X=88,
    K_Y=89,
    K_Z=90,
    K_LEFT_BRACKET=91,
    K_BACKSLASH=92,
    K_RIGHT_BRACKET=93,
    K_GRAVE_ACCENT=96,
    K_WORLD_1=161,
    K_WORLD_2=162,

    K_ESCAPE=256,
    K_ENTER=257,
    K_TAB=258,
    K_BACKSPACE=259,
    K_INSERT=260,
    K_DELETE=261,
    K_RIGHT=262,
    K_LEFT=263,
    K_DOWN=264,
    K_UP=265,
    K_PAGE_UP=266,
    K_PAGE_DOWN=267,
    K_HOME=268,
    K_END=269,
    K_CAPS_LOCK=280,
    K_SCROLL_LOCK=281,
    K_NUM_LOCK=282,
    K_PRINT_SCREEN=283,
    K_PAUSE=284,
    K_F1=290,
    K_F2=291,
    K_F3=292,
    K_F4=293,
    K_F5=294,
    K_F6=295,
    K_F7=296,
    K_F8=297,
    K_F9=298,
    K_F10=299,
    K_F11=300,
    K_F12=301,
    K_F13=302,
    K_F14=303,
    K_F15=304,
    K_F16=305,
    K_F17=306,
    K_F18=307,
    K_F19=308,
    K_F20=309,
    K_F21=310,
    K_F22=311,
    K_F23=312,
    K_F24=313,
    K_F25=314,
    K_KP_0=320,
    K_KP_1=321,
    K_KP_2=322,
    K_KP_3=323,
    K_KP_4=324,
    K_KP_5=325,
    K_KP_6=326,
    K_KP_7=327,
    K_KP_8=328,
    K_KP_9=329,
    K_KP_DECIMAL=330,
    K_KP_DIVIDE=331,
    K_KP_MULTIPLY=332,
    K_KP_SUBTRACT=333,
    K_KP_ADD=334,
    K_KP_ENTER=335,
    K_KP_EQUAL=336,
    K_LEFT_SHIFT=340,
    K_LEFT_CONTROL=341,
    K_LEFT_ALT=342,
    K_LEFT_SUPER=343,
    K_RIGHT_SHIFT=344,
    K_RIGHT_CONTROL=345,
    K_RIGHT_ALT=346,
    K_RIGHT_SUPER=347,
    K_MENU=348,
    K_LAST=348
};

enum class FInputMod: int {
    SHIFT=0x0001,
    CONTROL=0x0002,
    ALT=0x0004,
    SUPER=0x0008
//  CAPS_LOCK=0x0010,
//  NUM_LOCK=0x0020
};

#endif