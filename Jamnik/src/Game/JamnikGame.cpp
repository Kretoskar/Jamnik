#include "JamnikGame.h"

#include "Core/AssetsRegistry.h"
#include "Core/ECS/SimpleECS.h"

void JamnikGame::Init()
{
    Entity meshEntity = ECS::NewEntity();
    auto* meshEntityTransformComponent = ECS::AddComponent<TransformComponent>(meshEntity);
    auto* meshEntityMeshComponent = ECS::AddComponent<MeshComponent>(meshEntity);

    meshEntityTransformComponent->Move(glm::vec3(0.0f, 0.1f, 0.0f));
    meshEntityMeshComponent->material = Jamnik::AssetsRegistry::GetInstance().meshMaterial.get();
    meshEntityMeshComponent->mesh = Jamnik::AssetsRegistry::GetInstance().mesh.get();

    Entity lightEntity = ECS::NewEntity();
    auto* lightEntityTransformComponent = ECS::AddComponent<TransformComponent>(lightEntity);
    auto* lightEntityMeshComponent = ECS::AddComponent<MeshComponent>(lightEntity);
    auto* lightEntityLightComponent = ECS::AddComponent<LightComponent>(lightEntity);
    
    lightEntityTransformComponent->Move(glm::vec3(0.4f,0.4f,0.4f));
    lightEntityTransformComponent->Scale(glm::vec3(0.1f, 0.1f, 0.1f));
    lightEntityMeshComponent->material = Jamnik::AssetsRegistry::GetInstance().lightMaterial.get();
    lightEntityMeshComponent->mesh = Jamnik::AssetsRegistry::GetInstance().lightMesh.get();
    lightEntityLightComponent->lightColor = {1.0f, 1.0f, 1.0f, 1.0f};
}