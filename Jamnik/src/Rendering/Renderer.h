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

        std::unique_ptr<Shader> shader;

        std::unique_ptr<VBO> vbo;
        std::unique_ptr<EBO> ebo;
        std::unique_ptr<VAO> vao;
        
        std::unique_ptr<Texture> texture;
        std::unique_ptr<Camera> camera;
        std::unique_ptr<DebugRenderer> debugRenderer;

        Window* window;
    };
}
