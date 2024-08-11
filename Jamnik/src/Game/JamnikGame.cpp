#include "JamnikGame.h"

#include "Core/AssetsRegistry.h"
#include "Core/ECS/SimpleECS.h"

void JamnikGame::Init()
{
    Entity meshEntity = ECS::NewEntity();
    {
        {
            auto* meshEntityTransformComponent = ECS::AddComponent<TransformComponent>(meshEntity);
            meshEntityTransformComponent->Move(glm::vec3(0.0f, 0.1f, 0.0f));
            meshEntityTransformComponent->Scale(glm::vec3(0.1f, 0.1f, 0.1f));
        }
        
        {
            auto* meshEntityModelComponent = ECS::AddComponent<ModelComponent>(meshEntity);
    
            meshEntityModelComponent->model = Jamnik::AssetsRegistry::GetInstance().model.get();
            for (auto &mesh : meshEntityModelComponent->model->meshes)
            {
                mesh.material = Jamnik::AssetsRegistry::GetInstance().meshMaterial.get();
            }
        }
    }

    
    Entity lightEntity = ECS::NewEntity();
    {
        {
            auto* lightEntityTransformComponent = ECS::AddComponent<TransformComponent>(lightEntity);
            lightEntityTransformComponent->Move(glm::vec3(0.4f,0.4f,0.4f));
            lightEntityTransformComponent->Scale(glm::vec3(0.1f, 0.1f, 0.1f));
        }
        
        {
            auto* lightEntityMeshComponent = ECS::AddComponent<MeshComponent>(lightEntity);
            lightEntityMeshComponent->material = Jamnik::AssetsRegistry::GetInstance().lightMaterial.get();
            lightEntityMeshComponent->mesh = Jamnik::AssetsRegistry::GetInstance().lightMesh.get();
        }
        
        {
            auto* lightEntityLightComponent = ECS::AddComponent<LightComponent>(lightEntity);
            lightEntityLightComponent->lightColor = {1.0f, 1.0f, 1.0f, 1.0f};
        }
    }

    Entity lightEntity2 = ECS::NewEntity();
    {
        {
            auto* lightEntityTransformComponent = ECS::AddComponent<TransformComponent>(lightEntity2);
            lightEntityTransformComponent->Move(glm::vec3(0.4f,2.0f,0.4f));
            lightEntityTransformComponent->Scale(glm::vec3(0.1f, 0.1f, 0.1f));
        }
        
        {
            auto* lightEntityMeshComponent = ECS::AddComponent<MeshComponent>(lightEntity2);
            lightEntityMeshComponent->material = Jamnik::AssetsRegistry::GetInstance().lightMaterial.get();
            lightEntityMeshComponent->mesh = Jamnik::AssetsRegistry::GetInstance().lightMesh.get();
        }
        
        {
            auto* lightEntityLightComponent = ECS::AddComponent<LightComponent>(lightEntity2);
            lightEntityLightComponent->lightColor = {1.0f, 1.0f, 1.0f, 1.0f};
        }
    }
}