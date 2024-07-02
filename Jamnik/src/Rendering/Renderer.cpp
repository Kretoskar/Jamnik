#include "Renderer.h"

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

float lightVertices[] =
{ //     COORDINATES     //
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f
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

void Jamnik::Renderer::Init(Window* inWindow)
{
    window = inWindow;

    {
        meshTexture = std::make_unique<Texture>("content/base.png", GL_TEXTURE0, GL_RGB);
        meshTexture->Bind();
    
        meshShader = std::make_unique<Shader>("src/Rendering/Shaders/basic.frag", "src/Rendering/Shaders/basic.vert");
        meshShader->Bind();
        meshShader->AssignBaseTexture(*meshTexture);
    
        meshVao = std::make_unique<VAO>();
        meshVao->Bind();
    
        meshVbo = std::make_unique<VBO>(vertices, sizeof(vertices));
        meshEbo = std::make_unique<EBO>(indices, sizeof(indices));
    
        // position
        meshVao->LinkAttrib(*meshVbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
        // color
        meshVao->LinkAttrib(*meshVbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        // UV
        meshVao->LinkAttrib(*meshVbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    }

    {
        lightShader = std::make_unique<Shader>("src/Rendering/Shaders/light.frag", "src/Rendering/Shaders/light.vert");
        lightShader->Bind();
    
        lightVao = std::make_unique<VAO>();
        lightVao->Bind();
    
        lightVbo = std::make_unique<VBO>(lightVertices, sizeof(lightVertices));
        lightEbo = std::make_unique<EBO>(lightIndices, sizeof(lightIndices));

        lightVao->LinkAttrib(*lightVbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    }
    
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
    model = scale(model, glm::vec3(1.0f, 3.0f, 1.0f));
    
    meshShader->Bind();
    meshTexture->Bind();
    meshVao->Bind();

    meshShader->SetModelMatrix(model);
    camera->SetVPMatricesInShader(*meshShader);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

    model = translate(model, glm::vec3(1,2,1));
    
    lightShader->Bind();
    lightVao->Bind();

    lightShader->SetModelMatrix(model);
    camera->SetVPMatricesInShader(*lightShader);
    glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
    
    debugRenderer->Render();
}

void Jamnik::Renderer::Cleanup()
{
    meshVao->Delete();
    meshVbo->Delete();
    meshEbo->Delete();
    meshShader->Delete();
}
