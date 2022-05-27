#pragma once
#include <cstdint>
#include <vector>

class Texture2D {
public:
    Texture2D();
    ~Texture2D();
    Texture2D(const char* fileName);

    void Bind(int i);
    bool IsLoaded() const {return success;}

    bool LoadTextureFromFile(const char* fileName);
private:
    uint32_t handle;
    int32_t width;
    int32_t height;
    int32_t channels;
    bool success;
};