﻿#include "Renderer.h"

#include <iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "DebugRenderer.h"
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

void Jamnik::Renderer::Init(Window* inWindow)
{
    window = inWindow;
    
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

    camera = std::make_unique<Camera>(window, glm::vec3(0.0f, 0.0f, 2.0f));
    camera->Init();

    debugRenderer = std::make_unique<DebugRenderer>(camera.get());
    debugRenderer->Init();

    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
}

void Jamnik::Renderer::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    static float rot = 0;
    rot += 2;
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
    
    shader->Bind();
    texture->Bind();
    vao->Bind();

    shader->SetModelMatrix(model);
    camera->SetVPMatricesInShader(*shader);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

    debugRenderer->Render();
}

void Jamnik::Renderer::Cleanup()
{
    vao->Delete();
    vbo->Delete();
    ebo->Delete();
    shader->Delete();
}
