#pragma once
#include <memory>

#include "Camera.h"
#include "EBO.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "Shaders/Shader.h"

namespace Jamnik
{
    class Renderer
    {
    public:
        void Init();
        void Render();
        void Cleanup();

        std::unique_ptr<Shader> shader;
        std::unique_ptr<VBO> vbo;
        std::unique_ptr<EBO> ebo;
        std::unique_ptr<VAO> vao;
        std::unique_ptr<Texture> texture;
        std::unique_ptr<Camera> camera;
    };
}
