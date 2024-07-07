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
        void Init(Window* inWindow, std::shared_ptr<Camera> inCamera);
        void Render();

        std::shared_ptr<Camera> camera;

        Window* window;
    };
}
