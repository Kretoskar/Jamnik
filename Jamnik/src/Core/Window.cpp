#include <iostream>

#include "Window.h"
#include "Rendering/UserInterface.h"

#include "Logger.h"
#include "Rendering/Shaders/Shader.h"

bool Jamnik::Window::Init()
{
    if (!glfwInit())
    {
        LOG_ERROR("glfwInit() error")
        return false;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    _GLFWWindow = glfwCreateWindow(1920, 1080, "Jamnik", NULL, NULL);
    
    if (!_GLFWWindow)
    {
        LOG_ERROR("Failed to create GLFW window")
        glfwTerminate();
        return false;
    }

    BindWindowEvents();
    
    glfwMakeContextCurrent(_GLFWWindow);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERROR("Failed to initialize GLAD")
        return false;
    }

    glViewport(0, 0, 1920, 1080);
    glClearColor(0.15f, 0.5f, 1.0f, 1.0f);
    
    LOG_MESSAGE("Window successfully initialized")

    _ui = std::make_unique<UserInterface>();
    if (!_ui->Init(_GLFWWindow))
    {
        LOG_ERROR("Failed to initialize user interface")
        return false;
    }

    _renderer = std::make_unique<Renderer>();
    _renderer->Init();
    
    return true;
}

void Jamnik::Window::MainLoop()
{
    // force VSYNC
    glfwSwapInterval(1);
    
    while (!glfwWindowShouldClose(_GLFWWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        _renderer->Render();
        
        _ui->CreateFrame();
        _ui->Render();
        
        glfwSwapBuffers(_GLFWWindow);
        glfwPollEvents();   
    }
}

void Jamnik::Window::ShutDown()
{
    _ui->Cleanup();
    _renderer->Cleanup();
    glfwTerminate();
}

void Jamnik::Window::BindWindowEvents()
{
    /* Save the pointer to the instance as user pointer */
    glfwSetWindowUserPointer(_GLFWWindow, this);

    /* Use a lambda to get the pointer and call the member function */
    glfwSetWindowPosCallback(_GLFWWindow, [](GLFWwindow *win, int xpos, int ypos)
    {
        const auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
        thisWindow->HandleWindowMoveEvents(xpos, ypos);
    });

    glfwSetWindowIconifyCallback(_GLFWWindow, [](GLFWwindow *win, int minimized)
    {
        const auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
        thisWindow->HandleWindowMinimizedEvents(minimized);
    });

    glfwSetWindowMaximizeCallback(_GLFWWindow, [](GLFWwindow *win, int maximized)
    {
        const auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
        thisWindow->HandleWindowMaximizedEvents(maximized);
    });

    glfwSetWindowCloseCallback(_GLFWWindow, [](GLFWwindow *win)
    {
        const auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
        thisWindow->HandleWindowCloseEvents();
    });

    glfwSetKeyCallback(_GLFWWindow, [](GLFWwindow *win, int key, int scancode, int action, int mods)
    {
        const auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
        thisWindow->HandleKeyEvents(key, scancode, action, mods);
    });

    glfwSetMouseButtonCallback(_GLFWWindow, [](GLFWwindow *win, int button, int action, int mods)
    {
        const auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
        thisWindow->HandleMouseButtonEvents(button, action, mods);
    });

    glfwSetCursorPosCallback(_GLFWWindow, [](GLFWwindow *win, double xpos, double ypos)
    {
        const auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
        thisWindow->HandleMousePositionEvents(xpos, ypos);
    });

    glfwSetCursorEnterCallback(_GLFWWindow, [](GLFWwindow *win, int enter)
    {
        const auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
        thisWindow->HandleMouseEnterLeaveEvents(enter);
    });
}

void Jamnik::Window::HandleWindowMoveEvents(int xpos, int ypos)
{
    LOG_MESSAGE("Window moved: x: %i y: %i", xpos, ypos)
}

void Jamnik::Window::HandleWindowMinimizedEvents(int minimized)
{
    if (minimized)
    {
        LOG_MESSAGE("Window has been minimized")
    }
    else
    {
        LOG_MESSAGE("Window has been restored")
    }
}

void Jamnik::Window::HandleWindowMaximizedEvents(int maximized)
{
    if (maximized)
    {
        LOG_MESSAGE("Window has been maximized")
    }
    else
    {
        LOG_MESSAGE("Window has been restored")
    }
}

void Jamnik::Window::HandleWindowCloseEvents()
{
    LOG_MESSAGE("Window has been closed")
}

void Jamnik::Window::HandleKeyEvents(int key, int scancode, int action, int mods)
{
    std::string actionName;
    
    switch (action)
    {
    case GLFW_PRESS:
        actionName = "pressed";
        break;
    case GLFW_RELEASE:
        actionName = "released";
        break;
    case GLFW_REPEAT:
        actionName = "repeated";
        break;
    default:
        actionName = "invalid";
        break;
    }

    const char *keyName = glfwGetKeyName(key, 0);
    LOG_MESSAGE("key %s (key %i, scancode %i) %s", keyName, key, scancode, actionName.c_str())
}

void Jamnik::Window::HandleMouseButtonEvents(int button, int action, int mods)
{
    std::string actionName;
    switch (action)
    {
    case GLFW_PRESS:
        actionName = "pressed";
        break;
    case GLFW_RELEASE:
        actionName = "released";
        break;
    case GLFW_REPEAT:
        actionName = "repeated";
        break;
    default:
        actionName = "invalid";
        break;
    }

    std::string mouseButtonName;
    switch(button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
        mouseButtonName = "left";
        break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
        mouseButtonName = "middle";
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        mouseButtonName = "right";
        break;
    default:
        mouseButtonName = "other";
        break;
    }

    LOG_MESSAGE("%s mouse button (%i) %s", mouseButtonName.c_str(), button, actionName.c_str())
}

void Jamnik::Window::HandleMousePositionEvents(double xpos, double ypos)
{
    //LOG_MESSAGE(1, "%s: Mouse is at position %lf/%lf\n", __FUNCTION__, xpos, ypos);
}

void Jamnik::Window::HandleMouseEnterLeaveEvents(int enter)
{
    if (enter)
    {
        LOG_MESSAGE("Mouse entered window")
    }
    else
    {
        LOG_MESSAGE("Mouse left window")
    }
}
