
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
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "Window.h"
#include "Shader.h"
#include "IO/Joystick.h"
#include "IO/Keyboard.h"
#include "IO/Mouse.h"
#include "Camera.h"
#include "glm/trigonometric.hpp"


glm::mat4 mouseTranform = glm::mat4(1.f);
Camera gCamera(glm::vec3(0.0,0.0,3.f));
float deltaTime =0.f;
float lastFrame = 0.f;


void ProcesssInput(Window& window, Joystick& joystick,double dt)
{
    if (Keyboard::KeyWentDown(GLFW_KEY_ESCAPE)) {
        window.Close();
    }
    if (Keyboard::Key(GLFW_KEY_W))
    {
        gCamera.UpdateCameraPos(CameraDirection::FORWARD, dt);
    } else if (Keyboard::Key(GLFW_KEY_S))
    {
        gCamera.UpdateCameraPos(CameraDirection::BACKWARD, dt);
    } else if (Keyboard::Key(GLFW_KEY_A))
    {
        gCamera.UpdateCameraPos(CameraDirection::LEFT, dt);
    } else if (Keyboard::Key(GLFW_KEY_D))
    {
        gCamera.UpdateCameraPos(CameraDirection::RIGHT, dt);
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

    program.Use();
    program.SetUniform("texture1", 0);

    mainJ.Update();
    if (mainJ.IsPresent())
    {
        std::cerr<< mainJ.GetName() << "Is Present" << std::endl;
    }
    
    glEnable(GL_DEPTH_TEST);
    glm::mat4 model = glm::mat4(1.f);
    model = glm::rotate(model, glm::radians(45.f), glm::vec3(1, 0, 0.f));
    model = glm::rotate(model, glm::radians(45.f), glm::vec3(0, 1, 0.f));
   
    glm::mat4 view = glm::mat4(1.f);
    glm::mat4 projection = glm::mat4(1.f);

    while (!window.IsClosed()) {
        auto currentTime =glfwGetTime();
        deltaTime =currentTime - lastFrame;
        lastFrame = currentTime;

        ProcesssInput(window, mainJ, deltaTime);
        
        window.ClearWindow(0.2,0.3,0.3,1.0);
        texture1.Bind(0);
        program.Use();
        model = glm::rotate(model,glm::radians((float)glfwGetTime()/20.f), glm::vec3(0, 0, 1.f));
        program.SetUniformMatrix("model", model);
        view = gCamera.GetViewMatrix();
        projection = glm::perspective(glm::radians(45.0f), (float)1920.0f/1080.0f,0.1f, 1000.0f);
      
        program.SetUniformMatrix("view", view);
        program.SetUniformMatrix("projection", projection);
    
        vertex_buffer.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        window.SwapBuffer();
        window.PollEvent();
    }
    return 0;
}