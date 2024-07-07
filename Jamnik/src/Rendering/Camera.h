#pragma once
#include "Core/EventSystem.h"
#include "glm/glm.hpp"

namespace Jamnik
{
    class Window;
}

namespace Jamnik
{
    class Shader;
}

class Camera
{
    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(-0.5f, -0.5f, -0.5f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    
    int width = 1920;
    int height = 1080;
    
    float speed = 0.015f;
    float sensitivity = 100.0f;

    float FOVdeg = 120;
    float nearPlane = 0.01f;
    float farPlane = 1000;

    Jamnik::Window* window;
    bool bCanMove = false;
    bool bCanLook = false;
    
    bool bMovingForward = false;
    bool bMovingBackward = false;
    bool bMovingLeft = false;
    bool bMovingRight = false;

    glm::vec3 GetVelocity() const;
    
public:
    Camera(Jamnik::Window* inWindow, glm::vec3 position)
        : window(inWindow), Position(position) {}
    void Init();
    void Update();
    
    glm::vec3 GetRightVector() const;
    
    void OnRightMouseButtonClick(void* event);
    void OnRightMouseButtonRelease(void* event);
    
    void OnForwardPressed(void* payload);
    void OnForwardReleased(void* payload);

    void OnBackwardPressed(void* payload);
    void OnBackwardReleased(void* payload);

    void OnRightPressed(void* payload);
    void OnRightReleased(void* payload);

    void OnLeftPressed(void* payload);
    void OnLeftReleased(void* payload);

    void OnMouseMoved(void* payload);
    
    // Updates and exports the camera matrix to the Vertex Shader
    void SetVPMatricesInShader(Jamnik::Shader& shader);

    void SetCameraPosInShader(Jamnik::Shader& shader);
};
