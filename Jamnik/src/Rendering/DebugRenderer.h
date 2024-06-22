#pragma once
#include <memory>

#include "Camera.h"
#include "EBO.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "Shaders/Shader.h"

struct LineVertex
{
    LineVertex(glm::vec3 pos, glm::vec3 color)
        : x(pos.x), y(pos.y), z(pos.z), r(color.r), g(color.g), b(color.b) {}
    LineVertex(float x, float y, float z, float r, float g, float b)
        : x(x), y(y), z(z), r(r), g(g), b(b) {}
    
    float x, y, z;
    float r, g, b;
};

class DebugRenderer
{
public:
    DebugRenderer() : camera(nullptr) {}
    DebugRenderer(Camera* inCamera) : camera(inCamera) {}
    void Init();
    void Render();
    
    std::unique_ptr<Jamnik::Shader> shader;

    std::unique_ptr<VBO> lineVbo;
    std::unique_ptr<EBO> lineEbo;
    std::unique_ptr<VAO> lineVao;
    
    LineVertex lineVertices[12] =
    {
        {-10.0f, 0.0f,  0.0f,     0.83f, 0.70f, 0.44f},
        {10.0f, 0.0f,  0.0f,     0.83f, 0.70f, 0.44f},
    
        {-10.0f, 0.0f,  1.0f,     0.83f, 0.70f, 0.44f},
        {10.0f, 0.0f,  1.0f,     0.83f, 0.70f, 0.44f},
    
        {-10.0f, 0.0f,  -1.0f,     0.83f, 0.70f, 0.44f},
        {10.0f, 0.0f,  -1.0f,     0.83f, 0.70f, 0.44f},

        {0.0f, 0.0f,  -10.0f,     0.83f, 0.70f, 0.44f},
        {0.0f, 0.0f,  10.0f,     0.83f, 0.70f, 0.44f},

        {1.0f, 0.0f,  -10.0f,     0.83f, 0.70f, 0.44f},
        {1.0f, 0.0f,  10.0f,     0.83f, 0.70f, 0.44f},

        {-1.0f, 0.0f,  -10.0f,     0.83f, 0.70f, 0.44f},
        {-1.0f, 0.0f,  10.0f,     0.83f, 0.70f, 0.44f}
    };
    
   unsigned lineIndices[12] =
   {
       0,1,
       2,3,
       4,5,
       6,7,
       8,9,
       10,11
   };

    Camera* camera;
};
