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
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // TODO: delta time 
   
    Position += GetVelocity();
    
    view = glm::lookAt(Position, Position + Orientation, Up);

    projection = glm::perspective(glm::radians(FOVdeg), static_cast<float>(width) / static_cast<float>(height), nearPlane, farPlane);

    shader.SetViewMatrix(view);
    shader.SetProjectionMatrix(projection);
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
    
    //JAMNIK_BIND_EVENT(MouseButtonEvent::StaticType(GLFW_MOUSE_BUTTON_RIGHT, GLFW_RELEASE), OnRightMouseButtonRelease)
    
   //JAMNIK_BIND_EVENT(KeyboardEvent::StaticType(GLFW_KEY_W, GLFW_PRESS), OnForwardPressed)
   //JAMNIK_BIND_EVENT(KeyboardEvent::StaticType(GLFW_KEY_W, GLFW_RELEASE), OnForwardReleased)

   //JAMNIK_BIND_EVENT(KeyboardEvent::StaticType(GLFW_KEY_S, GLFW_PRESS), OnBackwardPressed)
   //JAMNIK_BIND_EVENT(KeyboardEvent::StaticType(GLFW_KEY_S, GLFW_RELEASE), OnBackwardReleased)

   //JAMNIK_BIND_EVENT(KeyboardEvent::StaticType(GLFW_KEY_D, GLFW_PRESS), OnRightPressed)
   //JAMNIK_BIND_EVENT(KeyboardEvent::StaticType(GLFW_KEY_D, GLFW_RELEASE), OnRightReleased)

   //JAMNIK_BIND_EVENT(KeyboardEvent::StaticType(GLFW_KEY_A, GLFW_PRESS), OnLeftPressed)
   //JAMNIK_BIND_EVENT(KeyboardEvent::StaticType(GLFW_KEY_A, GLFW_RELEASE), OnLeftReleased)

   //JAMNIK_BIND_EVENT(MousePositionEvent::StaticType(), OnMouseMoved)
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

/*

void Camera::OnForwardPressed(const Event& event)
{
    bMovingForward = true;
}

void Camera::OnForwardReleased(const Event& event)
{
    bMovingForward = false;
}

void Camera::OnBackwardPressed(const Event& event)
{
    bMovingBackward = true;
}

void Camera::OnBackwardReleased(const Event& event)
{
    bMovingBackward = false;
}

void Camera::OnRightPressed(const Event& event)
{
    bMovingRight = true;
}

void Camera::OnRightReleased(const Event& event)
{
    bMovingRight = false;
}

void Camera::OnLeftPressed(const Event& event)
{
    bMovingLeft = true;
}

void Camera::OnLeftReleased(const Event& event)
{
    bMovingLeft = false;
}

void Camera::OnMouseMoved(const Event& event)
{
    if (!bCanLook) return;
    
    const MousePositionEvent* mouseEvent = dynamic_cast<const MousePositionEvent*>(&event);
    float rotX = sensitivity * (float)(mouseEvent->GetPosY() - (height / 2)) / height;
    float rotY = sensitivity * (float)(mouseEvent->GetPosX() - (width / 2)) / width;

    glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

    // Decides whether or not the next vertical Orientation is legal or not
    if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
    {
        Orientation = newOrientation;
    }

    // Rotates the Orientation left and right
    Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

    glfwSetCursorPos(window->GetGLFWWindow(), (width / 2), (height / 2));
}
*/