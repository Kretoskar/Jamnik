#include "Components.h"

#include "Rendering/Mesh.h"
#include "Rendering/Material.h"

void TransformComponent::Move(glm::vec3 delta)
{
    position += delta;
    modelMatrix = translate(modelMatrix, delta);
}

void TransformComponent::Scale(glm::vec3 delta)
{
    scale *= delta;
    modelMatrix = glm::scale(modelMatrix, delta);
}
