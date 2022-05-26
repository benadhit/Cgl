cmake_minimum_required(VERSION 3.12)
project(Cgl CXX C)

include_directories(thirdparty/glad/include)
include_directories(thirdparty/stb)
add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glm)
add_executable(Cgl 
    thirdparty/glad/src/glad.c
    src/shader.cpp
    src/VertexBuffer.cpp
    src/IndexBuffer.cpp
    src/utils.cpp
    src/main.cpp)

target_link_libraries(Cgl PRIVATE glfw glm)