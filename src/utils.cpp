#include "utils.h"
#include <glad/glad.h>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include <cassert>
#include <cstddef>
#include <iostream>

namespace ShaderUtils {
std::string loadShaderSrc(const char* fileName)
{
    std::ifstream file;
    std::stringstream buf;

    std::string ret;
    file.open(fileName);
    if (file.is_open())
    {
        buf << file.rdbuf();
        ret = buf.str();
    }else {
        // log 
        std::cerr << "load file failed" << fileName << std::endl;
    }
    file.close();
    return ret;
}

bool CompileError(uint32_t shader_handle, std::string& error_msg)
{
    int success = 0;
    glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &success);
    char buf[512] ={0};
    if (!success)
    {
        error_msg.reserve(512);
        glGetShaderInfoLog(shader_handle, 512, nullptr, buf);
        error_msg  = std::string(buf);
        return false;
    }
    return true;
}

uint32_t createShader(const char * content, ShaderType type)
{
  uint32_t shader_type = 0;
    switch (type) {
        case ShaderType::VERTEX_SHADER:
            shader_type = GL_VERTEX_SHADER;
            break;
        case ShaderType::FRAGMENT_SHADER:
            shader_type = GL_FRAGMENT_SHADER;
            break;

         default:
            assert(0);
    }
    auto shader_handle = glCreateShader(shader_type);
    glShaderSource(shader_handle, 1, &content, nullptr);
    glCompileShader(shader_handle);
    auto error_msg =std::string();
    auto res =CompileError(shader_handle, error_msg);
    if (!res)
    {
        std::cerr<< "[ERROR]: " << error_msg << std::endl;
    }
    return shader_handle;
}
  
}