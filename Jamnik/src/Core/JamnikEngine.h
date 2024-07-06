#pragma once
#include <memory>

namespace Jamnik
{
    class Window;
    class Renderer;
    
    class JamnikEngine
    {
    public:
        bool Init();
        void Loop();
        void Exit();

    private:
        std::shared_ptr<Window> _window;
        std::shared_ptr<Renderer> _renderer;
    };
   
}
