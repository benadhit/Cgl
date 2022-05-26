#include "IndexBuffer.h"
#include <glad/glad.h>

IndexBuffer::IndexBuffer()
{
    glCreateBuffers(1, &handle);
}
IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &handle);
    handle =0;
}

void IndexBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
}

void IndexBuffer::UnBind()
{

}

void IndexBuffer::CopyDataToGpu(void *data, uint64_t size)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}