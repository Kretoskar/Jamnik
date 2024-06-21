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
    lineVao = std::make_unique<VAO>();
    lineVao->Bind();
    lineVbo = std::make_unique<VBO>(lineVertices, sizeof(lineVertices));
    lineEbo = std::make_unique<EBO>(lineIndices, sizeof(lineIndices));
    // position
    lineVao->LinkAttrib(*lineVbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    // color
    lineVao->LinkAttrib(*lineVbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // UV
    lineVao->LinkAttrib(*lineVbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
}

void DebugRenderer::Render()
{
    lineVao->Bind();
    glDrawElements(GL_LINES, sizeof(lineIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
}
