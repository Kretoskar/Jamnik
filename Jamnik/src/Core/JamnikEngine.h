#pragma once

#include <memory>

class UserInterface;

namespace Jamnik
{
    class Window;
    class Renderer;
    
    class JamnikEngine
    {
        JamnikEngine() {}
    
    public:
        JamnikEngine(JamnikEngine const&) = delete;
        void operator=(JamnikEngine const &) = delete;
    
        static JamnikEngine& GetInstance()
        {
            static JamnikEngine instance;
            return instance;
        }
        
        bool Init();
        void Loop();
        void Exit();

        std::shared_ptr<UserInterface> GetUI() const { return _ui; }
        
    private:
        std::shared_ptr<Window> _window;
        std::shared_ptr<Renderer> _renderer;
        std::shared_ptr<UserInterface> _ui;

        static JamnikEngine* Instance;
    };
   
}
