#include "Camera.h"

#include <GLFW/glfw3.h>

#include "Core/Logger.h"

void Camera::Init()
{
    JAMNIK_BIND_EVENT(MouseButtonEvent::Type(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0), OnLeftMouseButtonClick)
    JAMNIK_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_W, GLFW_PRESS, 0), OnForwardPressed)
}

void Camera::OnLeftMouseButtonClick(const Event& event)
{
    auto x = &Camera::OnForwardPressed;
    
    JAMNIK_LOG_WARNING("Button %i", dynamic_cast<const MouseButtonEvent*>(&event)->GetButton())
}

void Camera::OnForwardPressed(const Event& event)
{
    JAMNIK_LOG_WARNING("Button %i", dynamic_cast<const KeyboardEvent*>(&event)->GetKey())
}
