#pragma once
#include <memory>

#include "Camera.h"
#include "EBO.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "Shaders/Shader.h"

class DebugRenderer
{
public:
    void Init();
    void Render();
    
    std::unique_ptr<Jamnik::Shader> shader;

    std::unique_ptr<VBO> lineVbo;
    std::unique_ptr<EBO> lineEbo;
    std::unique_ptr<VAO> lineVao;

    float lineVertices[96] =
    {
        -10.0f, 0.0f,  0.0f,     0.83f, 0.70f, 0.44f, 	0.0f, 0.0f,
        10.0f, 0.0f,  0.0f,     0.83f, 0.70f, 0.44f, 	0.0f, 0.0f,
    
        -10.0f, 0.0f,  1.0f,     0.83f, 0.70f, 0.44f, 	0.0f, 0.0f,
        10.0f, 0.0f,  1.0f,     0.83f, 0.70f, 0.44f, 	0.0f, 0.0f,
    
        -10.0f, 0.0f,  -1.0f,     0.83f, 0.70f, 0.44f, 	0.0f, 0.0f,
        10.0f, 0.0f,  -1.0f,     0.83f, 0.70f, 0.44f, 	0.0f, 0.0f,

        0.0f, 0.0f,  -10.0f,     0.83f, 0.70f, 0.44f, 	0.0f, 0.0f,
        0.0f, 0.0f,  10.0f,     0.83f, 0.70f, 0.44f, 	0.0f, 0.0f,

        1.0f, 0.0f,  -10.0f,     0.83f, 0.70f, 0.44f, 	0.0f, 0.0f,
        1.0f, 0.0f,  10.0f,     0.83f, 0.70f, 0.44f, 	0.0f, 0.0f,

        -1.0f, 0.0f,  -10.0f,     0.83f, 0.70f, 0.44f, 	0.0f, 0.0f,
        -1.0f, 0.0f,  10.0f,     0.83f, 0.70f, 0.44f, 	0.0f, 0.0f,
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
};
