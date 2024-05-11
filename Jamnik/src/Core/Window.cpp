#include <iostream>

#include "Window.h"

bool Jamnik::Window::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    _window = glfwCreateWindow(1920, 1080, "Jamnik", NULL, NULL);
    if (_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glViewport(320, 0, 1280, 720);
    glClearColor(0.15f, 0.5f, 1.0f, 1.0f);

    return true;
}

void Jamnik::Window::ShutDown()
{
    glfwTerminate();
}
