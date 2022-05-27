
#include <memory>
#include <stdint.h>
#include <functional>

enum class render_backend : uint8_t {
    OPENGL,
    VULKAN,
    DIRECTX,
};

struct WindowProperties {
    int x;
    int y;
    int width;
    int height;
    const char* title;
    render_backend end;
};

enum class BufferType
{
    COLOR_BUFFER = 0x1,
    DEPTH_BUFFER = 0x10,
    ALL,
};

struct IO {

};

class Window {
public:
    Window(const WindowProperties& properties);
    virtual ~Window();

    bool IsSuccess();
    bool Resize(int width, int height);
    void ClearWindow(float r, float g , float b , float a, 
        BufferType buffer = BufferType::COLOR_BUFFER);

    void* GetBackEndWinddowHandle();

    void PollEvent();

    bool IsClosed();

    void SwapBuffer();    

    void Close();
private:
    std::unique_ptr<struct WindowImpl> impl_;
};