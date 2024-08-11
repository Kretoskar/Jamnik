#include "Renderer.h"

#include <iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "DebugRenderer.h"
#include "Core/AssetsRegistry.h"
#include "Core/EventSystem.h"
#include "Core/JamnikEngine.h"
#include "Core/Logger.h"
#include "Core/ECS/SimpleECS.h"

void Jamnik::Renderer::Init(Window* inWindow, std::shared_ptr<Camera> inCamera)
{
    window = inWindow;
    camera = inCamera;

    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
}

void Jamnik::Renderer::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::vector<Entity> entities;
    for (auto& entityIter : ECS::GetComponentArray<TransformComponent>()->components)
    {
        entities.emplace_back(entityIter.first);
    }

    glm::vec4 lightColor {};
    Entity lightEntity;
    
    for (auto& lightComponent : ECS::GetComponentArray<LightComponent>()->components)
    {
        lightColor = lightComponent.second.lightColor;
        lightEntity = lightComponent.first;
    }
    
    glm::vec3 lightPosition = ECS::GetComponent<TransformComponent>(lightEntity)->GetPosition();
    
    for (int i = 0; i < entities.size(); i++)
    {
        Entity e = entities[i];
        auto* transformComponent = ECS::GetComponent<TransformComponent>(e);
        auto* meshComponent = ECS::GetComponent<MeshComponent>(e);

        if (meshComponent)
        {
            meshComponent->material->Bind();
            meshComponent->material->Shader->SetModelMatrix(transformComponent->GetModelMatrix());
            meshComponent->material->Shader->SetLightColor(lightColor);
            meshComponent->material->Shader->SetLightPosition(lightPosition);
            meshComponent->material->Shader->SetVPMatrix(camera->GetVPMatrix());
            meshComponent->material->Shader->SetCameraPosition(camera->GetPosition());

            meshComponent->mesh->Draw();
        }

        auto* modelComponent = ECS::GetComponent<ModelComponent>(e);
        if (modelComponent)
        {
            for (auto &mesh : modelComponent->model->meshes)
            {
                mesh.material->Bind();
                mesh.material->Shader->SetModelMatrix(transformComponent->GetModelMatrix());
                mesh.material->Shader->SetLightColor(lightColor);
                mesh.material->Shader->SetLightPosition(lightPosition);
                mesh.material->Shader->SetVPMatrix(camera->GetVPMatrix());
                mesh.material->Shader->SetCameraPosition(camera->GetPosition());

                mesh.Draw();
            }
        }
    }
}
