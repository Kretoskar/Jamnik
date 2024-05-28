#include "Renderer.h"

#include <glad/glad.h>

// Vertices coordinates
float vertices[] =
{
    -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,       0.0f, 0.0f, // Lower left corner
    -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,       0.0f, 1.0f, // Upper left corner
     0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,       1.0f, 1.0f, // Upper right corner
     0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,       1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
unsigned indices[] =
{
    0, 2, 1, // Upper triangle
     0, 3, 2 // Lower triangle
};

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
}

void Jamnik::Renderer::Render()
{
    shader->Bind();
    texture->Bind();
    vao->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Jamnik::Renderer::Cleanup()
{
    vao->Delete();
    vbo->Delete();
    ebo->Delete();
    shader->Delete();
}
