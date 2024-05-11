#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    bool Init();
    void ShutDown();

    GLFWwindow* GetGlfwWindow() const { return _window; }
    
private:
    GLFWwindow* _window;
};
