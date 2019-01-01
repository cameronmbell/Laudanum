#include "laudanum/Fwindow.hpp"
#include "laudanum/FExcept.hpp"
#include "laudanum/Shader.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

int main(int argc, char* argv[]) {
    auto window = FWindow::create();

    if (window == nullptr)
        return 1;

    // build the shader program
    auto basic_shader = Shader::makeFromStrings(
        #include "shaders/vertex.glsl"
        ,
        #include "shaders/fragment.glsl"
    );

    if (!basic_shader)
        return 1;

    static const GLfloat vertex_data[] = {
        +0.5f,+0.5f, 0.0f, /* top right */ 1.0f, 0.0f, 0.0f, /* red */
        +0.5f,-0.5f, 0.0f, /* bot right */ 0.0f, 1.0f, 0.0f, /* green */
        -0.5f,+0.5f, 0.0f,  /* top left */ 0.0f, 0.0f, 1.0f  /* blue */
    };
    static const GLuint element_data[] = {
        0, 1, 2, /* first tri */
    };

    // 1. generate the buffers
    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // 2. bind the vertex array object and then the vbo
    // then copy verticies into a vertex buffer and element buffer
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_data), element_data, GL_STATIC_DRAW);

    // 3. set vertex attrib pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // 4. unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // enable wireframe rendering
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    for (;;) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 1. use shader program
        basic_shader->use();

        // 1.1 set uniforms
        auto elapsed_time = glfwGetTime();

        basic_shader->set1f("time", elapsed_time);

        // 2. rebind the vao
        glBindVertexArray(vao);

        // 3. draw the vbo based on the ebo (stored in vao)
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        // 4. swap the buffer
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
    // deallocate buffers
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    return 0;
}

// core rendering technique:
/*
Yes, but keep in mind the default frame buffer will always be the
same size of the window. What you can do is to render your scenes
internally into an off-screen (400x300) frame buffer, and then 
up-scale it to (800x600), you can do this by rendering this into 
a texture and applying it on a full screen quad, the advantage you 
will get is your shaders will run less often than with higher resolution. 
But you will lose quality due to scaling up which will need interpolating 
the original data in order to fill the bigger image.
*/

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