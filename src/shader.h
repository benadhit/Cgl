#pragma once

#include "glm/fwd.hpp"
#include <string>
#include <cstdint>


class ShaderProgram {
public:
    ShaderProgram(const char* vert, const char* frag);
    ~ShaderProgram();

    bool IsSuccess();

    std::string GetErrorMsg() const {return error_msg_;}

    void Use();

    void SetUniformMatrix(const char* name, glm::mat4& value);
    void SetUniformVec(const char* name, glm::vec4& value);
    void SetUniformVec(const char* name, glm::vec3& value);
    void SetUniformVec(const char* name, glm::vec2& value);
    void SetUniform(const char* name, float value);
    void SetUniform(const char* name, int value);


private:
    uint32_t GetUniformLocation(const char* name);

    uint32_t program_handle = 0;
    std::string error_msg_;
};