#include "shader.h"
#include "utils.h"
#include <glad/glad.h>


ShaderProgram::ShaderProgram(const char* vert, const char* frag)
{
    auto vertexShaderSrc = ShaderUtils::loadShaderSrc(vert);
    auto vert_handle = ShaderUtils::createShader(vertexShaderSrc.c_str(),
         ShaderType::VERTEX_SHADER);

    auto fragShaderSrc =ShaderUtils::loadShaderSrc(frag);
    auto frag_handle = ShaderUtils::createShader(fragShaderSrc.c_str(),
         ShaderType::FRAGMENT_SHADER);

    program_handle = glCreateProgram();
    glAttachShader(program_handle, vert_handle);
    glAttachShader(program_handle, frag_handle);
    glLinkProgram(program_handle);
    int sucess = 0;
    glGetProgramiv(program_handle, GL_LINK_STATUS, &sucess);
    char buf[512] ={0};
    if (!sucess)
    {
        glGetProgramInfoLog(program_handle, 512,nullptr, buf);
        error_msg_ = buf;
    }
    glDeleteShader(vert_handle);
    glDeleteShader(frag_handle);
}

ShaderProgram::~ShaderProgram() 
{
    if (program_handle != 0) {
        glDeleteProgram(program_handle);
        program_handle = 0;
    }
}

bool ShaderProgram::IsSuccess()
{
    return error_msg_.empty();
}

void ShaderProgram::Use()
{
    glUseProgram(program_handle);
}
