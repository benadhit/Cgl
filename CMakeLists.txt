cmake_minimum_required(VERSION 3.12)
project(Cgl CXX C)

include_directories(thirdparty/glad/include)
include_directories(thirdparty/stb)
add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glm)
add_executable(Cgl 
    thirdparty/glad/src/glad.c
    src/Shader.cpp
    src/Linux/LinuxWindow.cpp
    src/VertexBuffer.cpp
    src/Texture2D.cpp
    src/IndexBuffer.cpp
    src/IO/Joystick.cpp
    src/IO/Keyboard.cpp
    src/IO/Mouse.cpp
    src/Utils.cpp
    src/main.cpp)

target_link_libraries(Cgl PRIVATE glfw glm)