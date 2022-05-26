
#include <array>
#include <cstdint>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "window.h"
#include "shader.h"

int main()
{
    glfwInit();

    // 4.4
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Cgl", nullptr, nullptr);
    if (window == nullptr)
    {
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }
    glViewport(0, 0, 1920, 1080);

    auto call_back = [](GLFWwindow* window, int width, int height){
        glViewport(0,0, width, height);
    };
    glfwSetFramebufferSizeCallback(window, call_back);

    auto process_input = [=]() {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        } 
    };

    ShaderProgram program("../asset/vertex_core.vert", "../asset/fragment.frag");

    float vertices[] = {
        // pos               // color
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
    };

    std::cout << sizeof(float) <<" " << sizeof(vertices)<<std::endl;

    uint32_t indices[] = {
        0,1,2,
        3,0,2
    };
    std::cout << sizeof(indices) << std::endl;

    std::vector<VertexBufferLayout> layout = {
        {3, 3 * sizeof(float), GL_FLOAT},
        {3, 3 * sizeof(float), GL_FLOAT},
    };

    VertexBuffer vertex_buffer;
    vertex_buffer.Bind();
    vertex_buffer.CopyDataToGpu(vertices, sizeof(vertices));
    vertex_buffer.SetVertexBufferLayout(layout);


    IndexBuffer index_buferr;
    index_buferr.Bind();
    index_buferr.CopyDataToGpu(indices, sizeof(indices));


    if (!program.IsSuccess())
    {
        std::cerr << program.GetErrorMsg() << std::endl;
    }

    while (!glfwWindowShouldClose(window)) {
        process_input();

        program.Use();

        glClearColor(0.2,0.3,0.3,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        vertex_buffer.Bind();
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        index_buferr.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

     glfwDestroyWindow(window);
    // glfwTerminate();
    return 0;
}