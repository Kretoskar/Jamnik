#pragma once
#include "Core/EventSystem.h"
#include "glm/glm.hpp"

namespace Jamnik
{
    class Shader;
}

class Camera
{
    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    bool firstClick = true;
    
    int width;
    int height;
    
    float speed = 0.01f;
    float sensitivity = 100.0f;

    float FOVdeg = 120;
    float nearPlane = 0.1f;
    float farPlane = 1000;

    glm::vec3 Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    
public:
    Camera(int width, int height, glm::vec3 position)
        : width(width), height(height), Position(position) {}
    void Init();

    glm::vec3 GetRightVector() const;
    
    void OnLeftMouseButtonClick(const Event& event);
    
    void OnForwardPressed(const Event& event);
    void OnForwardReleased(const Event& event);

    void OnBackwardPressed(const Event& event);
    void OnBackwardReleased(const Event& event);

    void OnRightPressed(const Event& event);
    void OnRightReleased(const Event& event);

    void OnLeftPressed(const Event& event);
    void OnLeftReleased(const Event& event);
    
    // Updates and exports the camera matrix to the Vertex Shader
    void SetVPMatricesInShader(Jamnik::Shader& shader);
};
