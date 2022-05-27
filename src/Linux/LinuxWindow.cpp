#include "../window.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <memory>

struct WindowImpl {
    GLFWwindow* handle;
    WindowProperties properties;
    bool IsSuccess_;
    
};

void FramebufferReszieCallback(GLFWwindow* window, int width, int height)
{

}


Window::Window(const WindowProperties& properties)
    : impl_(std::make_unique<WindowImpl>())
{
    glfwInit();
    impl_->properties = properties;
    impl_->IsSuccess_ = true;
    switch (impl_->properties.end) {
        case render_backend::OPENGL: {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
        }
        case render_backend::DIRECTX: {

        }
        case render_backend::VULKAN: {

        }
    }
    impl_->handle = glfwCreateWindow(properties.width, properties.height, properties.title, 
    nullptr, nullptr);
    if (impl_->handle == nullptr)
    {
        impl_->IsSuccess_ = false;
        return;
    }
    glfwSetWindowUserPointer(impl_->handle, impl_.get());
    glfwMakeContextCurrent(impl_->handle);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        impl_-> IsSuccess_ =false; 
    }
    glViewport(properties.x, properties.y, properties.width, properties.height);
    glfwSetFramebufferSizeCallback(impl_->handle,
        [](GLFWwindow*window, int width, int height) {
            auto appData = (WindowImpl*)glfwGetWindowUserPointer(window);
            appData->properties.width = width;
            appData->properties.width = height;
            glViewport(appData->properties.x, appData->properties.y,
            width, height);
        } );
}

Window::~Window() {
    glfwDestroyWindow(impl_->handle);
    //glfwTerminate();
}

bool Window::IsSuccess()
{
    return impl_->IsSuccess_;
}

bool Window::Resize(int width, int height)
{
    impl_->properties.width = width;
    impl_->properties.height = height;
    glViewport(impl_->properties.x, impl_->properties.y,
    impl_->properties.width, impl_->properties.height);
    return true;
}

void Window::PollEvent()
{
    glfwPollEvents();
}

bool Window::isClosed()
{
    return glfwWindowShouldClose(impl_->handle);
} 

void Window::SwapBuffer()
{
    glfwSwapBuffers(impl_->handle);
}

void Window::ClearWindow(float r, float g, float b, float a, BufferType type)
{
    glClearColor(0.2,0.3,0.3,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}