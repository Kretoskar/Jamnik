#include "DebugRenderer.h"

#include "Renderer.h"

#include <iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Core/Color.h"
#include "Core/EventSystem.h"
#include "Core/Logger.h"

void DebugRenderer::Init()
{
    shader = std::make_unique<Jamnik::Shader>("src/Rendering/Shaders/debug.frag", "src/Rendering/Shaders/debug.vert");
    shader->Bind();
    
    lineVao = std::make_unique<VAO>();
    lineVao->Bind();
    lineVbo = std::make_unique<VBO>((float*)lineVertices, MAX_LINE_COUNT * 6 * 4);
    lineEbo = std::make_unique<EBO>(lineIndices, MAX_LINE_COUNT * 2 * 4);
    // position
    lineVao->LinkAttrib(*lineVbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    // color
    lineVao->LinkAttrib(*lineVbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    DrawNet(100, 1.0f, 100.0f, glm::vec3(0.6f, 0.6f, 0.6f));
    DrawNet(1000, 0.1f, 100.0f, glm::vec3(0.3f, 0.3f, 0.3f));
}

void DebugRenderer::Render()
{
    shader->Bind();
    camera->SetVPMatricesInShader(*shader);
    shader->SetModelMatrix(1.0f);
    lineVao->Bind();
    glDrawElements(GL_LINES, sizeof(lineIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void DebugRenderer::AddLine(glm::vec3 start, glm::vec3 end, glm::vec3 color)
{
    if (lineCount == MAX_LINE_COUNT)
    {
        JAMNIK_LOG_ERROR("Exceeded maximum debug line count of %d Can't draw any more lines", MAX_LINE_COUNT)
        return;
    }
    
    lineVertices[lineCount * 2] = {start, color};
    lineVertices[lineCount * 2 + 1] = {end, color};

    lineIndices[lineCount * 2] = lineCount * 2;
    lineIndices[lineCount * 2 + 1] = lineCount * 2 + 1;
    
    lineCount++;

    lineVao->Bind();
    lineVbo->Init((float*)lineVertices, lineCount * 2 * 6 * 4);
    lineEbo->Init(lineIndices, MAX_LINE_COUNT * 2 * 4);
    // position
    lineVao->LinkAttrib(*lineVbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    // color
    lineVao->LinkAttrib(*lineVbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}

void DebugRenderer::DrawNet(unsigned count, float stride, float size, glm::vec3 color)
{
    //TODO: Allow adding lines in batch
    for (int i = 0; i <= count; i++)
    {
        AddLine(glm::vec3(size/2, 0.0f, i * stride - count * stride / 2), glm::vec3(-size/2, 0.0f, i*stride - count * stride / 2), color);
        AddLine(glm::vec3(i * stride - count * stride / 2, 0.0f, size/2), glm::vec3(i*stride - count * stride / 2, 0.0f, -size/2), color);
    }
}
