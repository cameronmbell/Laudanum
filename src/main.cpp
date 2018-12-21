#include "laudanum/Fwindow.hpp"
#include "laudanum/FExcept.hpp"
#include "laudanum/FShader.hpp"

#include <glad/glad.h>
#include <string>


int main(int argc, char* argv[]) {
    auto window = FWindow::create();

    if (window == nullptr)
        return 1;

    GLuint vao;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    static const GLfloat vertex_data[] = {
    -1.0f, -0.5f, 0.0f,
    1.0f, -0.5f, 0.0f,
    0.0f,  1.0f, 0.0f,
    1.0f, 0.5f, 0.0f,
    -1.0f, 0.5f, 0.0f,
    0.0f, -1.0f, 0.0f,
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    for (;;) {
        glClear(GL_COLOR_BUFFER_BIT);

//        glEnableVertexAttribArray(0);

        glDrawArrays(GL_TRIANGLES, 0, 6);
 //       glDisableVertexAttribArray(0);

        window->draw();

        FInputEvent event;
        while (window->getEvent(event)) {
            /**/ if (event.type == FInputType::WIN_CLOSE)
                goto cleanup;
            else if (event.type == FInputType::K_DOWN
                  && event.button == FInputButton::K_ESCAPE 
                  && !FINPUT_HAS_MOD(event.mods, FInputMod::CONTROL))
                  goto cleanup;
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