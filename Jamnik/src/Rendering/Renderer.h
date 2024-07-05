#pragma once
#include <memory>

#include "Camera.h"
#include "DebugRenderer.h"
#include "EBO.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "Shaders/Shader.h"

class Window;

namespace Jamnik
{
    class Renderer
    {
    public:
        void Init(Window* inWindow);
        void Render();
        void Cleanup();

        std::unique_ptr<Shader> meshShader;
        std::unique_ptr<Shader> lightShader;

        std::unique_ptr<Mesh> mesh;
        std::unique_ptr<Mesh> lightMesh;

        glm::vec4 lightColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        
        std::unique_ptr<Texture> meshDiffuseMap;
        std::unique_ptr<Texture> meshSpecularMap;

        std::unique_ptr<Material> meshMaterial;
        std::unique_ptr<Material> lightMaterial;
        
        std::unique_ptr<Camera> camera;
        std::unique_ptr<DebugRenderer> debugRenderer;

        Window* window;
    };
}
