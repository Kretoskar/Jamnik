#include "Camera.h"

#include <GLFW/glfw3.h>

#include "Core/Logger.h"

void Camera::Init()
{
    Dispatcher::GetInstance().Subscribe(MouseButtonEvent::Type(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0),
        std::bind(&Camera::OnLeftMouseButtonClick, this, std::placeholders::_1));

    Dispatcher::GetInstance().Subscribe(KeyboardEvent::Type(GLFW_KEY_W, GLFW_PRESS, 0),
        std::bind(&Camera::OnForwardPressed, this, std::placeholders::_1));
}

void Camera::OnLeftMouseButtonClick(const Event& event)
{
    LOG_WARNING("Button %i", dynamic_cast<const MouseButtonEvent*>(&event)->GetButton())
}

void Camera::OnForwardPressed(const Event& event)
{
    LOG_WARNING("Button %i", dynamic_cast<const KeyboardEvent*>(&event)->GetKey())
}
