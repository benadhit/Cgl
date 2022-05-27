#pragma once 
#include <cstdint>
#include <string>


enum ShaderType {
    VERTEX_SHADER,
    FRAGMENT_SHADER,
};

template<ShaderType type>
struct Shader {
   static constexpr ShaderType value = type;
   Shader();

public:
    uint32_t handle;
};


namespace ShaderUtils {
   std::string loadShaderSrc(const char* fileName);
   uint32_t createShader(const char* content, ShaderType type);
   bool CompileError(uint32_t shader_handle, std::string& error_msg);
}