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

    // TODO: delta time 
    
    Position += Velocity;
    view = glm::lookAt(Position, Position + Orientation, Up);

    projection = glm::perspective(glm::radians(FOVdeg), static_cast<float>(width) / static_cast<float>(height), nearPlane, farPlane);

    shader.SetViewMatrix(view);
    shader.SetProjectionMatrix(projection);
}

void Camera::Init()
{
    JAMNIK_BIND_EVENT(MouseButtonEvent::Type(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS), OnLeftMouseButtonClick)
    
    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_W, GLFW_PRESS), OnForwardPressed)
    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_W, GLFW_RELEASE), OnForwardReleased)

    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_S, GLFW_PRESS), OnBackwardPressed)
    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_S, GLFW_RELEASE), OnBackwardReleased)

    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_D, GLFW_PRESS), OnRightPressed)
    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_D, GLFW_RELEASE), OnRightReleased)

    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_A, GLFW_PRESS), OnLeftPressed)
    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_A, GLFW_RELEASE), OnLeftReleased)
}

glm::vec3 Camera::GetRightVector() const
{
    return glm::normalize(glm::cross(Orientation, Up));
}

void Camera::OnLeftMouseButtonClick(const Event& event)
{
    JAMNIK_LOG_WARNING("Button %i", dynamic_cast<const MouseButtonEvent*>(&event)->GetButton())
}

void Camera::OnForwardPressed(const Event& event)
{
    Velocity += Orientation * speed;
}

void Camera::OnForwardReleased(const Event& event)
{
    Velocity -= Orientation * speed;
}

void Camera::OnBackwardPressed(const Event& event)
{
    Velocity += -Orientation * speed;
}

void Camera::OnBackwardReleased(const Event& event)
{
    Velocity -= -Orientation * speed;
}

void Camera::OnRightPressed(const Event& event)
{
    Velocity += GetRightVector() * speed;
}

void Camera::OnRightReleased(const Event& event)
{
    Velocity -= GetRightVector() * speed;
}

void Camera::OnLeftPressed(const Event& event)
{
    Velocity += -GetRightVector() * speed;
}

void Camera::OnLeftReleased(const Event& event)
{
    Velocity -= -GetRightVector() * speed;
}
