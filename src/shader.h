#pragma once

#include <string>
#include <cstdint>


class ShaderProgram {
public:
    ShaderProgram(const char* vert, const char* frag);
    ~ShaderProgram();

    bool IsSuccess();

    std::string GetErrorMsg() const {return error_msg_;}

    void Use();


private:
    uint32_t program_handle = 0;
    std::string error_msg_;
};