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
    LineVertex() = default;

    LineVertex(glm::vec3 pos, glm::vec3 color)
        : x(pos.x), y(pos.y), z(pos.z), r(color.r), g(color.g), b(color.b) {}
    LineVertex(float x, float y, float z, float r, float g, float b)
        : x(x), y(y), z(z), r(r), g(g), b(b) {}
    
    float x{}, y{}, z{};
    float r{}, g{}, b{};
};

class DebugRenderer
{
public:
    DebugRenderer() : camera(nullptr) {}
    DebugRenderer(Camera* inCamera) : camera(inCamera) {}
    void Init();
    void Render();
    void AddLine(glm::vec3 start, glm::vec3 end, glm::vec3 color);
    void DrawNet(unsigned count, float stride, float size, glm::vec3 color);
    
    std::unique_ptr<Jamnik::Shader> shader;

    std::unique_ptr<VBO> lineVbo;
    std::unique_ptr<EBO> lineEbo;
    std::unique_ptr<VAO> lineVao;

    static constexpr unsigned MAX_LINE_COUNT = 4096;
    unsigned lineCount = 0;
    LineVertex lineVertices[MAX_LINE_COUNT * 2];
    
    unsigned lineIndices[MAX_LINE_COUNT * 2];

    Camera* camera;
};
