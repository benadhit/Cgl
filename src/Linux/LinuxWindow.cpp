#include "../Window.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <memory>
#include "../IO/Keyboard.h"
#include "../IO/Mouse.h"
#include "../IO/Joystick.h"
struct WindowImpl {
    GLFWwindow* handle;
    WindowProperties properties;
    bool IsSuccess_;
};

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
    glfwSetWindowUserPointer(impl_->handle, this);
    glfwMakeContextCurrent(impl_->handle);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        impl_-> IsSuccess_ =false; 
    }
    glViewport(properties.x, properties.y, properties.width, properties.height);

    glfwSetFramebufferSizeCallback(impl_->handle,
        [](GLFWwindow*window, int width, int height) {
            auto appData = (Window*)glfwGetWindowUserPointer(window);
            appData->Resize(width, height);
        } );
    glfwSetKeyCallback(impl_->handle,[](GLFWwindow* window,int key, int scan_code, int action,int mods) {
            auto appData = (Window*)glfwGetWindowUserPointer(window);
            Keyboard::KeyCallBack(*appData, key, scan_code, action, mods);
            });
    glfwSetCursorPosCallback(impl_->handle,
      [](GLFWwindow* window, double x, double y){
         auto appData = (Window*)glfwGetWindowUserPointer(window);
          Mouse::CursorPosCallback(*appData, x, y);
      });

    glfwSetMouseButtonCallback(impl_->handle,
        [](GLFWwindow* window, int button, int action, int mods){
         auto appData = (Window*)glfwGetWindowUserPointer(window);
        Mouse::MouseButtonCallback(*appData, button, action,mods);

        });
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

bool Window::IsClosed()
{
    return glfwWindowShouldClose(impl_->handle);
} 

void Window::SwapBuffer()
{
    glfwSwapBuffers(impl_->handle);
}

void Window::Close()
{
    glfwSetWindowShouldClose(impl_->handle, GLFW_TRUE);
}

void Window::ClearWindow(float r, float g, float b, float a, BufferType type)
{
    switch (type) {
    case BufferType::COLOR_BUFFER:
       glClear(GL_COLOR_BUFFER_BIT);
        break;
    case BufferType::DEPTH_BUFFER:
        glClearColor(r,g,b,a);
       glClear(GL_DEPTH_BUFFER_BIT);
        break;
    case BufferType::ALL:
        glClearColor(r,g,b,a);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       break;
    default:
        glClearColor(r,g,b,a);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);   
    }
}

void* Window::GetBackEndWinddowHandle()
{
    return impl_->handle;
}