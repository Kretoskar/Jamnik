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
        bool Init();
        void MainLoop();
        void ShutDown();
    
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
        std::unique_ptr<Renderer> _renderer;
    };
}
