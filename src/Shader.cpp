#include "Shader.h"
#include "Utils.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

void ShaderProgram::SetUniformMatrix(const char* name, glm::mat4& value)
{
    return glUniformMatrix4fv(GetUniformLocation(name),1, GL_FALSE,glm::value_ptr(value));
}

void ShaderProgram::SetUniformMatrix(const char* name, glm::mat3& value)
{
    return glUniformMatrix3fv(GetUniformLocation(name),1, GL_FALSE,glm::value_ptr(value));
}

void ShaderProgram::SetUniformMatrix(const char* name, glm::mat2& value)
{
    return glUniformMatrix2fv(GetUniformLocation(name),1, GL_FALSE,glm::value_ptr(value));
}


uint32_t ShaderProgram::GetUniformLocation(const char* name)
{
    return glGetUniformLocation(program_handle,name);
}

void ShaderProgram::SetUniformVec(const char* name, glm::vec4& value)
{
    return glUniform4fv(GetUniformLocation(name),1, glm::value_ptr(value));
}

void ShaderProgram::SetUniformVec(const char* name, glm::vec3& value)
{
    return glUniform3fv(GetUniformLocation(name),1, glm::value_ptr(value));
}
void ShaderProgram::SetUniformVec(const char* name, glm::vec2& value)
{
    return glUniform2fv(GetUniformLocation(name),1, glm::value_ptr(value));
}
void ShaderProgram::SetUniform(const char* name, float value)
{
    return glUniform1f(GetUniformLocation(name), value);
}
void ShaderProgram::SetUniform(const char* name, int value)
{
   return glUniform1i(GetUniformLocation(name), value);
}