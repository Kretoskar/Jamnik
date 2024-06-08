#include "Camera.h"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Core/Logger.h"
#include "Shaders/Shader.h"

void Camera::SetVPMatricesInShader(Jamnik::Shader& shader)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    
    view = glm::lookAt(Position, Position + Orientation, Up);

    projection = glm::perspective(glm::radians(FOVdeg), static_cast<float>(width) / static_cast<float>(height), nearPlane, farPlane);

    shader.SetViewMatrix(view);
    shader.SetProjectionMatrix(projection);
}

void Camera::Init()
{
    JAMNIK_BIND_EVENT(MouseButtonEvent::Type(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS), OnLeftMouseButtonClick)
    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_W, GLFW_PRESS), OnForwardPressed)
}

void Camera::OnLeftMouseButtonClick(const Event& event)
{
    JAMNIK_LOG_WARNING("Button %i", dynamic_cast<const MouseButtonEvent*>(&event)->GetButton())
}

void Camera::OnForwardPressed(const Event& event)
{
    JAMNIK_LOG_WARNING("Button %i", dynamic_cast<const KeyboardEvent*>(&event)->GetKey())
}
