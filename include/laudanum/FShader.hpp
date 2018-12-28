#ifndef _F_SHADER_HPP
#define _F_SHADER_HPP

#include "FExcept.hpp"

#include <glad/glad.h>
#include <list>

#define FSHADER_COMPILER_ERR_L 1024

// what type of shader to load
enum class FShaderType : GLenum;

namespace FShader {
    // load a shader of type from its source
    // returns 0 on fail otherwise the shader id
    GLuint load(FShaderType type, const char* source);

    // link a shader program from a list of compiled shaders
    // returns 0 on fail otherwise the program id
    GLuint makeProgram(const std::list<GLuint>& source_list, bool* success_state=nullptr);

    namespace _details {
        extern char error_buffer [FSHADER_COMPILER_ERR_L];

        constexpr const char* typeToLiteral(FShaderType shader_type) {
            return 
            (static_cast<GLenum>(shader_type) == GL_VERTEX_SHADER) ? "VERTEX" :
            (static_cast<GLenum>(shader_type) == GL_GEOMETRY_SHADER) ? "GEOMETRY" :
            (static_cast<GLenum>(shader_type) == GL_FRAGMENT_SHADER) ? "FRAGMENT" :
            "<unknown>";
        }
    }
};

enum class FShaderType : GLenum {
    VERTEX=GL_VERTEX_SHADER,
    GEOMETRY=GL_GEOMETRY_SHADER,
    FRAGMENT=GL_FRAGMENT_SHADER
};

#endif