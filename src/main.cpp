#include "laudanum/Fwindow.hpp"
#include "laudanum/FExcept.hpp"

int main(int argc, char* argv[]) {
    auto window = FWindow::create();

    for (;;) {
        FInputEvent event;
        while (window->getEvent(event)) {
            /**/ if (event.type == FInputType::WIN_CLOSE)
                goto cleanup;
            else if (event.type == FInputType::K_DOWN
                  && event.button == FInputButton::K_ESCAPE 
                  && !FINPUT_HAS_MOD(event.mods, FInputMod::CONTROL))
                  goto cleanup;
            else if (event.type == FInputType::K_DOWN)
                FLog("Key down on key: %d w/ mods: %d", event.button, event.mods);
            else if (event.type == FInputType::K_UP)
                FLog("Key up on key: %d w/ mods: %d", event.button, event.mods);
            else if (event.type == FInputType::MB_DOWN)
                FLog("MB down on button: %d w/ mods: %d", event.button, event.mods);
            else if (event.type == FInputType::MB_UP)
                FLog("MB up on button: %d w/ mods: %d", event.button, event.mods);
            else if (event.type == FInputType::M_MOVE)
                FLog("Mouse move to (%f, %f)", event.x, event.y);
            else
                FLog("Unknown event");
        }
    }

cleanup:
    return 0;
}

// a possible architecture taken from youtube...
/*
int main(int argc, char* argv[]) {
    Scene* scene = new Menu();
    Window window();

    for (;;) {
        scene->render(window);

        RawEvent raw_event;
        while (window.getEvent(raw_event)) {
            GameEvent game_event;

            if (InputMapper::parseEvent(raw_event, game_event)) {
                scene.handleEvent(raw_event);
                if (!scene)
                    return 0;
            }
        }
    }

    return 0;
}

struct Scene {
    virtual Scene* update(double delta_time)=0;
    virtual Scene* handleEvent(const GameEvent& event)=0;
    virtual void render(Window& window) const=0;
    virtual ~Scene();
}

struct InputMapper {
    Map<RawEvent, GameEvent> event_map;

    InputMapper() {
        event_map[RawEvent::Escape] = GameEvent::Pause;
    }

    bool parseEvent(const RawEvent& raw_event, GameEvent& game_event) {
        if (bindings.contains(raw_event)) {
            game_event = bindings[raw_event];
        } else if (raw_event == RawEvent::WindowClose) {
            game_event = GameEvent::quit;
        }

        return false;
    }
}

// todo use singleton
InputMapper gimap;
*/