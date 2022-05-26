#include "../window.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <memory>

struct WindowImpl {
    GLFWwindow* hanlde;
    static WindowProperties properties;
    bool IsSuccess_;
    
};

void FramebufferReszieCallback(GLFWwindow* window, int width, int height)
{

}


Window::Window(const WindowProperties& properties)
    : impl_(std::make_unique<WindowImpl>())
{
    impl_->properties = properties;
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
    impl_->hanlde = glfwCreateWindow(properties.width, properties.height, properties.title, 
    nullptr, nullptr);
    if (impl_->hanlde == nullptr)
    {
        impl_->IsSuccess_ = false;
    }
    glfwSetWindowUserPointer(impl_->hanlde, impl_.get());
    glfwMakeContextCurrent(impl_->hanlde);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        impl_-> IsSuccess_ =false; 
    }
    glViewport(properties.x, properties.y, properties.width, properties.height);
//     glfwSetFramebufferSizeCallback(impl_->hanlde,
//         [](GLFWwindow*window, int width, int height) {
//             auto appData = (WindowImpl*)glfwGetWindowUserPointer(window);
//             appData->properties.width = width;
//             appData->properties.width = height;
//         } );
}

Window::~Window() {
    glfwDestroyWindow(impl_->hanlde);
    glfwTerminate();
}

bool Window::Resize(int width, int height)
{
    impl_->properties.width = width;
    impl_->properties.height = height;
    glViewport(impl_->properties.x, impl_->properties.y,
    impl_->properties.width, impl_->properties.height);
    return true;
}