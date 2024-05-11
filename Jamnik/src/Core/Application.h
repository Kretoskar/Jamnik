#pragma once

#include "imgui/imgui_impl_glfw.h"


class Application
{
public:
    bool Start();
    void Update();
    void ShutDown();

    bool GetShouldClose() const { return _shouldClose; }
    
private:
    bool _shouldClose = false;
    GLFWwindow* _window;
};

