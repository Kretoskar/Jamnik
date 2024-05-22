#pragma once
#include <memory>

#include "EBO.h"
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
    };
}
