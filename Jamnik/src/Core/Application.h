#pragma once

#include <memory>

#include "Window.h"


class Application
{
public:
    bool Init();
    void Update();
    void ShutDown();

    bool GetShouldClose() const { return _shouldClose; }
    
private:
    std::unique_ptr<Window> _window;
    bool _shouldClose = false;
};

