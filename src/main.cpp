
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
#include "window.h"
#include "shader.h"

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
        // pos               // color           // texture coord
        -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.5f,  0.0, 0.0,
        -0.5f,  0.5f, 0.0f,  0.5f, 1.0f, 0.75f, 0.0, 1.0,
         0.5f, -0.5f, 0.0f,  0.6f, 1.0f, 0.2f,  1.0, 0.0,
         0.5f,  0.5f, 0.0f,  1.0f, 0.2f, 1.0f,  1.0, 1,0,
    };
    uint32_t indices[] = {
        0,1,2,
        3,1,2
    };

    std::vector<VertexBufferLayout> layout = {
        {3, 3 * sizeof(float), GL_FLOAT},
        {3, 3 * sizeof(float), GL_FLOAT},
        {2, 2 * sizeof(float), GL_FLOAT},
    };

    VertexBuffer vertex_buffer;
    vertex_buffer.Bind();
    vertex_buffer.CopyDataToGpu(vertices, sizeof(vertices));
    vertex_buffer.SetVertexBufferLayout(layout);

    IndexBuffer index_buferr;
    index_buferr.Bind();
    index_buferr.CopyDataToGpu(indices, sizeof(indices));

    glm::mat4 trans = glm::mat4(1.f);
    //trans = glm::rotate(trans, glm::radians(45.f), glm::vec3(0, 0, 1.f));
    program.Use();
    program.SetUniform("texture1", 0);
    while (!window.isClosed()) {
        window.PollEvent();
        window.ClearWindow(0.2,0.3,0.3,1.0);
        texture1.Bind(0);
        program.Use();
        // trans = glm::rotate(trans,glm::radians((float)glfwGetTime()/20.f), glm::vec3(0, 0, 1.f));
        program.SetUniformMatrix("transform", trans);
    
        vertex_buffer.Bind();
        index_buferr.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        window.SwapBuffer();
    }
    return 0;
}