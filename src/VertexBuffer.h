#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

enum DataType
{
    UINT8,
    INT8,
    UINT16,
    INT16,
    UINT32,
    INT32,
    UINT64,
    INT64,
    FLOAT,
    DOUBLE,  
};

struct VertexBufferLayout 
{
    uint32_t elem_count;
    uint32_t total_size;
    uint32_t elem_type;
};

class VertexBuffer {
public:
    VertexBuffer();

    ~VertexBuffer();

    void Bind();

    void UnBind();

    void CopyDataToGpu(void* data, size_t size);

    void SetVertexBufferLayout(std::vector<VertexBufferLayout>& layout);

private:
    uint32_t vao;
    uint32_t vbo;
    uint32_t total_size;
    uint32_t num_vertices;
};
