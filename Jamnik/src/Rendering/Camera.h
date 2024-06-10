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
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    int width = 1920;
    int height = 1080;
    
    float speed = 0.1f;
    float sensitivity = 100.0f;

    float FOVdeg = 120;
    float nearPlane = 0.1f;
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

    glm::vec3 GetRightVector() const;
    
    void OnRightMouseButtonClick(const Event& event);
    void OnRightMouseButtonRelease(const Event& event);
    
    void OnForwardPressed(const Event& event);
    void OnForwardReleased(const Event& event);

    void OnBackwardPressed(const Event& event);
    void OnBackwardReleased(const Event& event);

    void OnRightPressed(const Event& event);
    void OnRightReleased(const Event& event);

    void OnLeftPressed(const Event& event);
    void OnLeftReleased(const Event& event);

    void OnMouseMoved(const Event& event);
    
    // Updates and exports the camera matrix to the Vertex Shader
    void SetVPMatricesInShader(Jamnik::Shader& shader);
};
