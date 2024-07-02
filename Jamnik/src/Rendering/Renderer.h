#pragma once
#include <memory>

#include "Camera.h"
#include "DebugRenderer.h"
#include "EBO.h"
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

        std::unique_ptr<VBO> meshVbo;
        std::unique_ptr<EBO> meshEbo;
        std::unique_ptr<VAO> meshVao;

        std::unique_ptr<VBO> lightVbo;
        std::unique_ptr<EBO> lightEbo;
        std::unique_ptr<VAO> lightVao;

        glm::vec4 lightColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        
        std::unique_ptr<Texture> meshTexture;
        std::unique_ptr<Camera> camera;
        std::unique_ptr<DebugRenderer> debugRenderer;

        Window* window;
    };
}
