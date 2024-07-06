#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "Rendering/Renderer.h"
#include "Rendering/UserInterface.h"

namespace Jamnik
{
    class Window
    {
    public:
        Window(int width, int height)
            : width(width), height(height) {}
        
        bool Init();
        void Update();
        void ShutDown();

        GLFWwindow* GetGLFWWindow() const { return _GLFWWindow; }

        int GetWidth() const { return width; }
        int GetHeight() const { return height; }

        UserInterface* GetUserInterface() const { return _ui.get(); }

        bool GetShouldClose();
        
    private:
        void BindWindowEvents();

        void HandleWindowMoveEvents(int xpos, int ypos);
        void HandleWindowMinimizedEvents(int minimized);
        void HandleWindowMaximizedEvents(int maximized);
        void HandleWindowCloseEvents();

        void HandleKeyEvents(int key, int scancode, int action, int mods);
        void HandleMouseButtonEvents(int button, int action, int mods);
        void HandleMousePositionEvents(double xpos, double ypos);
        void HandleMouseEnterLeaveEvents(int enter);
        
        GLFWwindow* _GLFWWindow = nullptr;

        std::unique_ptr<UserInterface> _ui;

        int width, height;
    };
}
