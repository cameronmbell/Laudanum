#ifndef _SHADER_HPP
#define _SHADER_HPP

#include "FStandard.hpp"
#include "FShader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

// Handle a compiled OpenGL shader program within it's own instance
// This is obviously an illusion since OpenGL is a state machine
// But it's convenient.
struct Shader {
    // The GL shader identifier
    const GLuint ID;

    // Constructors, handled by factory functions
    Shader() = delete;
    Shader(const Shader&) = delete;
    Shader(GLuint id) noexcept : ID(id) { }
    Shader(Shader&& o) noexcept : ID(std::move(o.ID)) { }

    // Function factory to build from raw strings
    // This is used with the following pattern
    // auto shdr = Shader::makeFromStrings(
    // #include "vertex.glsl"
    // ,
    // #include "fragment.glsl"   
    // );
    // if (!shdr) { [error] }
    static std::unique_ptr<Shader> makeFromStrings(
        const char* vertex_source, 
        const char* fragment_source) {
        
        bool build_success;

        auto shader_program = FShader::makeProgram({
            FShader::load(FShaderType::VERTEX,
                vertex_source
            ), FShader::load(FShaderType::FRAGMENT,
                fragment_source
            )
        }, &build_success);

        if (build_success == 0)
            return nullptr;
        
        return FStandard::makeUnique<Shader>(shader_program);
    }

    static std::unique_ptr<Shader> makeFromFiles(
        const std::string& vertex_file_path,
        const std::string& fragment_file_path
    );

    // Tell OpenGL to make this shader the current one in use
    inline void use() const 
    { glUseProgram(ID); }

    // Set uniform variables
    inline void set1f(const char* key, GLfloat value) const
    { glUniform1f(glGetUniformLocation(ID, key), value); }
    inline void set1i(const char* key, GLint value) const
    { glUniform1i(glGetUniformLocation(ID, key), value); }
    inline void setMatrix4x4(const char* key, const glm::mat4& value) const 
    { glUniformMatrix4fv(glGetUniformLocation(ID, key), 1, GL_FALSE, glm::value_ptr(value)); }
};

#endif