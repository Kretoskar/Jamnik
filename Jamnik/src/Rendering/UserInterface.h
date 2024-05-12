#pragma once

#include <GLFW/glfw3.h>

class UserInterface
{
public:
    bool Init(GLFWwindow* window);
    void CreateFrame();
    void Render();
    void Cleanup();

private:
    float _framesPerSecond = 0.0f;
    /* averaging speed */
    float _averagingAlpha = 0.96f;
};
