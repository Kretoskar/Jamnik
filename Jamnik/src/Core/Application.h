#pragma once

#include <memory>

#include "Window.h"

namespace Jamnik
{
    class Application
    {
    public:
        bool Init();
        void Update();
        void ShutDown();

        bool GetShouldClose() const { return _shouldClose; }
    
    private:
        std::unique_ptr<Jamnik::Window> _window;
        bool _shouldClose = false;
    };
}