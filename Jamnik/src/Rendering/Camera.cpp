#include "Camera.h"

#include <GLFW/glfw3.h>

#include "Core/Logger.h"

void Camera::Init()
{
    Dispatcher::GetInstance().Subscribe(MouseButtonEvent(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0).Type(),
        std::bind(&Camera::OnLeftMouseButtonClick, this, std::placeholders::_1));
}

void Camera::OnLeftMouseButtonClick(const Event& event)
{
    LOG_WARNING(event.Type().c_str())
}
