#pragma once
#include <cstdint>

class IndexBuffer {
public:
    IndexBuffer();

    ~IndexBuffer();

    void Bind();

    void UnBind();

    void CopyDataToGpu(void* data, uint64_t size);

private:
    unsigned int handle = 0;
};