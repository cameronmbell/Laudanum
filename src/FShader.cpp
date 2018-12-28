#include "laudanum/FShader.hpp"

namespace FShader {

char _details::error_buffer [FSHADER_COMPILER_ERR_L];

GLuint load(FShaderType type, const char* source) {
    GLuint shader = glCreateShader(static_cast<GLenum>(type));

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, sizeof(_details::error_buffer), nullptr, _details::error_buffer);
        glDeleteShader(shader);

        FErr("%s shader failed to compile, and was deleted: \n%s", 
            _details::typeToLiteral(type),
            _details::error_buffer);

        return 0;
    }

    return shader;
}

GLuint makeProgram(const std::list<GLuint>& source_list, bool* success_state) {
    GLuint shader_program = glCreateProgram();

    // compile each shader separatly and attach them to the program
    for (const auto& shader : source_list) {
        if (!shader) FWarn("Did not attach shader %d because it doesn't exist", shader);
        else         glAttachShader(shader_program, shader);
    }

    // link anc check success state
    glLinkProgram(shader_program);

    int success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shader_program, sizeof(_details::error_buffer), nullptr, _details::error_buffer);

        FErr("Failed to link shaders: \n%s", _details::error_buffer);
    }

    // now that program has not linked: delete
    for (const auto& shader : source_list)
        if (shader)
            glDeleteShader(shader);

    /* @todo
     * glValidateProgram()
     */

    if (success_state)
        *success_state = !!success;

    return shader_program;
}
};