
#include <array>
#include <cstdint>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ostream>
#include <vector>
#include "IndexBuffer.h"
#include "Texture2D.h"
#include "VertexBuffer.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "Window.h"
#include "Shader.h"
#include "IO/Joystick.h"
#include "IO/Keyboard.h"
#include "IO/Mouse.h"

glm::mat4 mouseTranform = glm::mat4(1.f);

void ProcesssInput(Window& window, Joystick& joystick)
{
    if (Keyboard::KeyWentDown(GLFW_KEY_ESCAPE)) {
        window.Close();
    }
}

int main()
{
    WindowProperties properties;
    properties.x = 0;
    properties.y = 0;
    properties.width = 1920;
    properties.height= 1080;
    properties.title ="Cgl";
    properties.end = render_backend::OPENGL;
    Window window(properties);
    if (!window.IsSuccess()) {
        // error;
    }
    Joystick mainJ(0);
    ShaderProgram program("../asset/vertex_core.vert", "../asset/fragment.frag");
    if (!program.IsSuccess())
    {
        std::cerr << program.GetErrorMsg() << std::endl;
        return -1;
    }
    Texture2D texture1;
    if (!texture1.LoadTextureFromFile("../asset/texture_human.jpg"))
    {
        std::cerr << "load texture failed"<<std::endl;
    }
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    std::vector<VertexBufferLayout> layout = {
        {3, 3 * sizeof(float), GL_FLOAT},
        {2, 2 * sizeof(float), GL_FLOAT},
    };

    VertexBuffer vertex_buffer;
    vertex_buffer.Bind();
    vertex_buffer.CopyDataToGpu(vertices, sizeof(vertices));
    vertex_buffer.SetVertexBufferLayout(layout);

    glm::mat4 trans = glm::mat4(1.f);
    trans = glm::rotate(trans, glm::radians(45.f), glm::vec3(1, 0, 0.f));
    trans = glm::rotate(trans, glm::radians(45.f), glm::vec3(0, 1, 0.f));
   
    program.Use();
    program.SetUniform("texture1", 0);

    mainJ.Update();
    if (mainJ.IsPresent())
    {
        std::cerr<< mainJ.GetName() << "Is Present" << std::endl;
    }
    glEnable(GL_DEPTH_TEST);
    
    while (!window.IsClosed()) {
        ProcesssInput(window, mainJ);
        window.ClearWindow(0.2,0.3,0.3,1.0);
        texture1.Bind(0);
        program.Use();
        trans = glm::rotate(trans,glm::radians((float)glfwGetTime()/20.f), glm::vec3(0, 0, 1.f));
        program.SetUniformMatrix("transform", trans);
    
        vertex_buffer.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        window.SwapBuffer();
        window.PollEvent();
    }
    return 0;
}