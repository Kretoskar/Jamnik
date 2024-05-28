#include "Renderer.h"

#include <glad/glad.h>

// Vertices coordinates
float vertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
     0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
     0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
    -0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
     0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
     0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
};

// Indices for vertices order
unsigned indices[] =
{
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Lower right triangle
    5, 4, 1 // Upper triangle
};

void Jamnik::Renderer::Init()
{
    shader = std::make_unique<Shader>("src/Rendering/Shaders/basic.frag", "src/Rendering/Shaders/basic.vert");
    shader->Bind();
    shader->SetUniform1f("scale", 2);
    
    vao = std::make_unique<VAO>();
    vao->Bind();
    
    vbo = std::make_unique<VBO>(vertices, sizeof(vertices));
    ebo = std::make_unique<EBO>(indices, sizeof(indices));

    // position
    vao->LinkAttrib(*vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    // color
    vao->LinkAttrib(*vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}

void Jamnik::Renderer::Render()
{
    shader->Bind();
    vao->Bind();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}

void Jamnik::Renderer::Cleanup()
{
    vao->Delete();
    vbo->Delete();
    ebo->Delete();
    shader->Delete();
}
