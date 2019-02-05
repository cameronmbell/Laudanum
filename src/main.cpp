#include "laudanum/FWindow.hpp"
#include "laudanum/FExcept.hpp"
#include "laudanum/Shader.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/std_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
        +1.0f,+1.0f,0.0f, /* top right */ 1.0f, 1.0f,
        +1.0f,-1.0f,0.0f, /* bot right */ 1.0f, 0.0f,
        -1.0f,-1.0f,0.0f,  /* bot left */ 0.0f, 0.0f,
        -1.0f,+1.0f,0.0f,  /* top left */ 0.0f, 1.0f
    };

    static const GLuint element_data[] = {
        0, 1, 2, /* first tri */
        2, 0, 3, /* secnd tri */
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*5, (void*)(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*5, (void*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // 4. unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLuint texture0;
    glGenTextures(1, &texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);

    int width, height, bits;
    stbi_set_flip_vertically_on_load(true);
    auto portrait_data = stbi_load("res/portrait0.jpg", &width, &height, &bits, 0);
    FLog("Read texture: portrait0.jpg of %dx%d and depth %d", width, height, bits);

    FAssert(portrait_data);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, portrait_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    stbi_image_free(portrait_data);

    // enable wireframe rendering
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // connect texture units
    basic_shader->use();
    basic_shader->set1i("texture0", 0);

    for (;;) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 0. bind texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);

        // 1. use shader program
        basic_shader->use();

        // 1.1 set uniforms
        float elapsed_time = static_cast<float>(glfwGetTime());
        glm::mat4 trans_mat = glm::mat4(1.0f);
        trans_mat = glm::scale(trans_mat, glm::vec3(0.5f));
        trans_mat = glm::translate(trans_mat, glm::vec3(std::sin(elapsed_time), std::cos(elapsed_time), 0.0f));
        trans_mat = glm::rotate(trans_mat, elapsed_time * FStandard::m_pif(0.25f), glm::vec3(1.0f, 1.0f, 1.0f));

        basic_shader->setMatrix4x4("uTransform", trans_mat);

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
