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
    
    float speed = 0.1f;
    float sensitivity = 100.0f;

    float FOVdeg = 120;
    float nearPlane = 0.1f;
    float farPlane = 1000;
    
public:
    Camera(int width, int height, glm::vec3 position)
        : width(width), height(height), Position(position) {}
    void Init();

    void OnLeftMouseButtonClick(const Event& event);
    void OnForwardPressed(const Event& event);

    // Updates and exports the camera matrix to the Vertex Shader
    void SetVPMatricesInShader(Jamnik::Shader& shader);
};
