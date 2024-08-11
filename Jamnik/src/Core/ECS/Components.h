#pragma once
#include <glm/fwd.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "Rendering/Model.h"

namespace Jamnik
{
    struct Material;
}

class Mesh;

struct TransformComponent
{
    void Move(glm::vec3 delta);
    void Scale(glm::vec3 delta);
    
    const glm::vec3& GetPosition() const { return position; }
    const glm::vec3& GetScale() const { return scale; }
    const glm::mat4& GetModelMatrix() const { return modelMatrix; }
    
private:
    glm::vec3 position {0.0f, 0.0f, 0.0f};
    glm::vec3 scale {1.0f, 1.0f, 1.0f};
    glm::mat4 modelMatrix = glm::mat4(1.0f);
};

struct MeshComponent
{
    Mesh* mesh;
    Jamnik::Material* material;
};

struct LightComponent
{
    glm::vec4 lightColor;
};

struct ModelComponent
{
    Model* model;
};