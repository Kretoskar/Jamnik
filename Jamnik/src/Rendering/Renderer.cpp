#include "Renderer.h"

#include <iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/EventSystem.h"
#include "Core/Logger.h"

// Vertices coordinates
float vertices[] =
{
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
unsigned indices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};

void OnEvent(const Event& event)
{
    LOG_WARNING(event.Type().c_str())
}

void Jamnik::Renderer::Init()
{
    texture = std::make_unique<Texture>("content/base.png", GL_TEXTURE0, GL_RGB);
    texture->Bind();
    
    shader = std::make_unique<Shader>("src/Rendering/Shaders/basic.frag", "src/Rendering/Shaders/basic.vert");
    shader->Bind();
    shader->AssignBaseTexture(*texture);
    
    vao = std::make_unique<VAO>();
    vao->Bind();
    
    vbo = std::make_unique<VBO>(vertices, sizeof(vertices));
    ebo = std::make_unique<EBO>(indices, sizeof(indices));

    // position
    vao->LinkAttrib(*vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    // color
    vao->LinkAttrib(*vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // UV
    vao->LinkAttrib(*vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    Dispatcher::GetInstance().Subscribe(MouseButtonEvent(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS,0).Type(), OnEvent);
    
    glEnable(GL_DEPTH_TEST);
}

void Jamnik::Renderer::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    static float rot = 0;
    rot += 2;
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
    
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)1920/1080, 0.1f, 100.0f);
    shader->SetMVPMatrices(model, view, projection);
    
    shader->Bind();
    texture->Bind();
    vao->Bind();
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void Jamnik::Renderer::Cleanup()
{
    vao->Delete();
    vbo->Delete();
    ebo->Delete();
    shader->Delete();
}
