#pragma once
#include <memory>

namespace Jamnik
{
    class Window;
    
    class JamnikEngine
    {
    public:
        bool Init();
        void Loop();
        void Exit();

    private:
        std::shared_ptr<Window> window;
    };
   
}
