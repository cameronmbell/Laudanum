#ifndef _F_SHADER_HPP
#define _F_SHADER_HPP

#include "FExcept.hpp"

#include <glad/glad.h>

#define  FSHADER_COMPILER_ERR_L 1024

#define _FSHADER_TYPES \
    X(VERTEX) \
    X(GEOMETRY) \
    X(FRAGMENT)

namespace FShader {
    enum class Type : GLenum {
#define X(_n) _n = GL_ ## _n ## _SHADER,
        _FSHADER_TYPES
#undef X
    };

    namespace _details {
        constexpr const char* typeToLiteral(Type type) {
        return 
#define X(_n) (static_cast<GLenum>(type) == GL_ ## _n ## _SHADER) ? #_n :
            _FSHADER_TYPES
            "<unknown";
        }
    };

    bool load(Type type, GLuint& shader, const char* source) {
        static char error_buffer [ FSHADER_COMPILER_ERR_L ];

        shader = glCreateShader(static_cast<GLenum>(type));

        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(shader, sizeof(error_buffer), nullptr, error_buffer);

            FErr("%s shader failed to compile: \n%s", 
                _details::typeToLiteral(type),
                error_buffer);
        }

        return success;
    }
};

#endif