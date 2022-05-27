#include "Texture2D.h"
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <vector>

Texture2D::Texture2D()
    :handle(0), width(0), height(0), success(false)
{
    glGenTextures(1, &handle);
}

Texture2D::Texture2D(const char* fileName)
{
    glGenTextures(1, &handle);
    width = 0;
    height = 0;
    success = false;
    LoadTextureFromFile(fileName);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &handle);
}

void Texture2D::Bind(int i)
{
    glActiveTexture(GL_TEXTURE0+ i);
    glBindTexture(GL_TEXTURE_2D, handle);
}

bool Texture2D::LoadTextureFromFile(const char *fileName)
{
    success =true;
    stbi_set_flip_vertically_on_load(true);
    glBindTexture(GL_TEXTURE_2D, handle);
    auto data = stbi_load(fileName, &width, &height, &channels, 0);
    if (data == nullptr)
    {
        success = false;
        return success;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
   
    stbi_set_flip_vertically_on_load(false);
    stbi_image_free(data);

    return success;
}