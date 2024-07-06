#include "AssetsRegistry.h"

#include "Rendering/Texture.h"
#include "Rendering/Shaders/Shader.h"

#include <glad/glad.h>

void Jamnik::AssetsRegistry::Init()
{
    meshDiffuseMap = std::make_shared<Texture>("content/diffuse.png", 0, GL_RGB);
    meshSpecularMap = std::make_shared<Texture>("content/specular.png", 1, GL_RED);
    meshShader = std::make_shared<Shader>("src/Rendering/Shaders/basic.frag", "src/Rendering/Shaders/basic.vert");
    lightShader = std::make_shared<Shader>("src/Rendering/Shaders/light.frag", "src/Rendering/Shaders/light.vert");
}

void Jamnik::AssetsRegistry::Cleanup()
{
    meshShader->Delete();
    lightShader->Delete();
}
