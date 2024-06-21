#include "DebugRenderer.h"

#include "Renderer.h"

#include <iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Core/EventSystem.h"
#include "Core/Logger.h"

void DebugRenderer::Init()
{
    shader = std::make_unique<Jamnik::Shader>("src/Rendering/Shaders/debug.frag", "src/Rendering/Shaders/debug.vert");
    shader->Bind();
    
    lineVao = std::make_unique<VAO>();
    lineVao->Bind();
    lineVbo = std::make_unique<VBO>(lineVertices, sizeof(lineVertices));
    lineEbo = std::make_unique<EBO>(lineIndices, sizeof(lineIndices));
    // position
    lineVao->LinkAttrib(*lineVbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    // color
    lineVao->LinkAttrib(*lineVbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}

void DebugRenderer::Render()
{
    shader->Bind();
    camera->SetVPMatricesInShader(*shader);
    shader->SetModelMatrix(1.0f);
    lineVao->Bind();
    glDrawElements(GL_LINES, sizeof(lineIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
}
