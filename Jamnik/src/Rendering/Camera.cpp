#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/glm.hpp"

#include "Core/Logger.h"
#include "Core/Window.h"
#include "Shaders/Shader.h"

#include<glm/glm.hpp>
#include "UserInterface.h"
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

void Camera::SetVPMatricesInShader(Jamnik::Shader& shader)
{
    shader.SetViewMatrix(view);
    shader.SetProjectionMatrix(projection);
}

void Camera::SetCameraPosInShader(Jamnik::Shader& shader)
{
    shader.SetCameraPosition(Position);
}

glm::vec3 Camera::GetVelocity() const
{
    glm::vec3 retVelocity = glm::vec3(0.0f, 0.0f, 0.0f);

    if (!bCanMove)
    {
        return {0.0f, 0.0f, 0.0f};
    }

    if (bMovingForward)
    {
        retVelocity += Orientation * speed;
    }
    if (bMovingBackward)
    {
        retVelocity -= Orientation * speed;
    }
    if (bMovingRight)
    {
        retVelocity += GetRightVector() * speed;
    }
    if (bMovingLeft)
    {
        retVelocity -= GetRightVector() * speed;
    }

    return retVelocity;
}

void Camera::Init()
{
    width = window->GetWidth();
    height = window->GetHeight();

    window->GetUserInterface()->RegisterCameraSpeedVarPtr(&speed);
    window->GetUserInterface()->RegisterCameraSensitivityVarPtr(&sensitivity);
    
    JAMNIK_BIND_EVENT(MouseButtonEvent::Type(GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS, 0), OnRightMouseButtonClick)
    JAMNIK_BIND_EVENT(MouseButtonEvent::Type(GLFW_MOUSE_BUTTON_RIGHT, GLFW_RELEASE, 0), OnRightMouseButtonRelease)

    JAMNIK_BIND_EVENT(MousePositionEvent::Type(), OnMouseMoved)
    
    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_W, GLFW_PRESS, 0), OnForwardPressed)
    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_W, GLFW_RELEASE, 0), OnForwardReleased)
    
    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_S, GLFW_PRESS, 0), OnBackwardPressed)
    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_S, GLFW_RELEASE, 0), OnBackwardReleased)
    
    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_D, GLFW_PRESS, 0), OnRightPressed)
    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_D, GLFW_RELEASE, 0), OnRightReleased)
    
    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_A, GLFW_PRESS, 0), OnLeftPressed)
    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_A, GLFW_RELEASE, 0), OnLeftReleased)
}

void Camera::Tick()
{
    Position += GetVelocity();

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(FOVdeg), static_cast<float>(width) / static_cast<float>(height), nearPlane, farPlane);
}

glm::vec3 Camera::GetRightVector() const
{
    return glm::normalize(glm::cross(Orientation, Up));
}

void Camera::OnRightMouseButtonClick(void* event)
{
    bCanMove = true;
    bCanLook = true;
    glfwSetCursorPos(window->GetGLFWWindow(), (width / 2), (height / 2));
    glfwSetInputMode(window->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Camera::OnRightMouseButtonRelease(void* event)
{
    bCanMove = false;
    bCanLook = false;
    glfwSetInputMode(window->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Camera::OnMouseMoved(void* payload)
{
    const int posX = *static_cast<int*>(payload);
    const int posY = *reinterpret_cast<int*>(static_cast<char*>(payload) + sizeof(int));

    if (!bCanLook) return;

    const float rotX = sensitivity * static_cast<float>(posY - (height / 2)) / height;
    const float rotY = sensitivity * static_cast<float>(posX - (width / 2)) / width;

    const glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

    // Decides whether or not the next vertical Orientation is legal or not
    if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
    {
        Orientation = newOrientation;
    }

    // Rotates the Orientation left and right
    Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
    
    glfwSetCursorPos(window->GetGLFWWindow(), (width / 2), (height / 2));
}

void Camera::OnForwardPressed(void* payload)
{
    bMovingForward = true;
}

void Camera::OnForwardReleased(void* payload)
{
    bMovingForward = false;
}

void Camera::OnBackwardPressed(void* payload)
{
    bMovingBackward = true;
}

void Camera::OnBackwardReleased(void* payload)
{
    bMovingBackward = false;
}

void Camera::OnRightPressed(void* payload)
{
    bMovingRight = true;
}

void Camera::OnRightReleased(void* payload)
{
    bMovingRight = false;
}

void Camera::OnLeftPressed(void* payload)
{
    bMovingLeft = true;
}

void Camera::OnLeftReleased(void* payload)
{
    bMovingLeft = false;
}
