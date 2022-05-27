#include "VertexBuffer.h"
#include <cstdint>
#include <glad/glad.h>

VertexBuffer::VertexBuffer()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
}  

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void VertexBuffer::Bind() 
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VertexBuffer::UnBind()
{
    glBindVertexArray(0);
}

void VertexBuffer::SetVertexBufferLayout(std::vector<VertexBufferLayout>& layout)
{
    uint8_t offset_begin = 0;
    uint32_t total_begin = 0;
    for (size_t i = 0; i <layout.size(); i++)
    {
        total_begin += layout[i].total_size;
    }

    for (int i = 0; i < layout.size(); ++i) {
        glVertexAttribPointer(i, layout[i].elem_count, layout[i].elem_type,
        GL_FALSE, total_begin, (void*)(offset_begin));
        offset_begin += layout[i].total_size;
        glEnableVertexAttribArray(i);
    }
    num_vertices = static_cast<uint32_t>(total_size / offset_begin);
}

void VertexBuffer::CopyDataToGpu(void* data, size_t size)
{
    this->total_size = size;
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

