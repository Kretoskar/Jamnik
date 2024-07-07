#include "AssetsRegistry.h"

#include "Rendering/Mesh.h"
#include "Rendering/Texture.h"
#include "Rendering/Shaders/Shader.h"
#include "Rendering/Material.h"

#include "Rendering/Vertex.h"
#include <glad/glad.h>

Vertex vertices[] =
{ 
    Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
    Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

unsigned indices[] =
{
    0, 1, 2,
    0, 2, 3
};

Vertex lightVertices[] =
{
    Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
    Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
    Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
    Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

unsigned lightIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};

void Jamnik::AssetsRegistry::Init()
{
    meshDiffuseMap = std::make_shared<Texture>("content/diffuse.png", 0, GL_RGB);
    meshSpecularMap = std::make_shared<Texture>("content/specular.png", 1, GL_RED);
    meshShader = std::make_shared<Shader>("src/Rendering/Shaders/basic.frag", "src/Rendering/Shaders/basic.vert");
    lightShader = std::make_shared<Shader>("src/Rendering/Shaders/light.frag", "src/Rendering/Shaders/light.vert");

    meshMaterial = std::make_shared<Material>(
    meshDiffuseMap.get(),
    meshSpecularMap.get(),
    *meshShader);
        
    mesh = std::make_shared<Mesh>(
        std::vector <Vertex>(vertices, vertices + sizeof(vertices) / sizeof(Vertex)),
        std::vector <unsigned> (indices, indices + sizeof(indices) / sizeof(GLuint)),
        meshMaterial.get());

    lightMaterial = std::make_unique<Material>(nullptr, nullptr, *lightShader);
        
    lightMesh = std::make_unique<Mesh>(std::vector <Vertex> (
        lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex)),
        std::vector <unsigned> (lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint)),
        lightMaterial.get());
}

void Jamnik::AssetsRegistry::Cleanup()
{
    meshShader->Delete();
    lightShader->Delete();
}
