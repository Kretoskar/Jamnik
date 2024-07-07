#include "Renderer.h"

#include <iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "DebugRenderer.h"
#include "Core/AssetsRegistry.h"
#include "Core/EventSystem.h"
#include "Core/JamnikEngine.h"
#include "Core/Logger.h"

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

void Jamnik::Renderer::Init(Window* inWindow, std::shared_ptr<Camera> inCamera)
{
    window = inWindow;
    camera = inCamera;
    
    {
        meshMaterial = std::make_unique<Material>(
            Jamnik::JamnikEngine::GetInstance().GetAssetsRegistry()->meshDiffuseMap.get(),
            Jamnik::JamnikEngine::GetInstance().GetAssetsRegistry()->meshSpecularMap.get(),
            *Jamnik::JamnikEngine::GetInstance().GetAssetsRegistry()->meshShader);

        std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
        std::vector <unsigned> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
        
        mesh = std::make_unique<Mesh>(verts, ind, meshMaterial.get());
    }

    {
        lightMaterial = std::make_unique<Material>(nullptr, nullptr, *Jamnik::JamnikEngine::GetInstance().GetAssetsRegistry()->lightShader);
    
        std::vector <Vertex> verts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
        std::vector <unsigned> ind(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
        
        lightMesh = std::make_unique<Mesh>(verts, ind, lightMaterial.get());
    }

    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
}

void Jamnik::Renderer::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glm::mat4 lightModelMat = glm::mat4(1.0f);
    glm::vec3 lightPos = glm::vec3(0.4f,0.4f,0.4f);
    lightModelMat = translate(lightModelMat, lightPos);
    lightModelMat = scale(lightModelMat, glm::vec3(0.1f, 0.1f, 0.1f));

    lightMaterial->Bind();
    
    lightMaterial->Shader->SetModelMatrix(lightModelMat);
    lightMaterial->Shader->SetLightColor(lightColor);
    lightMaterial->Shader->SetVPMatrix(camera->GetVPMatrix());
    lightMesh->Draw();
    
    meshMaterial->Bind();

    glm::mat4 meshModelMat = glm::mat4(1.0f);
    meshModelMat = translate(meshModelMat, glm::vec3(0.0f, 0.1f, 0.0f));
    meshMaterial->Shader->SetModelMatrix(meshModelMat);
    meshMaterial->Shader->SetLightColor(lightColor);
    meshMaterial->Shader->SetLightPosition(lightPos);
    meshMaterial->Shader->SetVPMatrix(camera->GetVPMatrix());
    meshMaterial->Shader->SetCameraPosition(camera->GetPosition());
    
    mesh->Draw();
}
