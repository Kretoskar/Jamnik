#pragma once

#include <memory>

class Camera;

namespace Jamnik
{
    class AssetsRegistry;
}

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
        std::shared_ptr<AssetsRegistry> GetAssetsRegistry() const { return _assetsRegistry; }
        
    private:
        std::shared_ptr<Window> _window;
        std::shared_ptr<Renderer> _renderer;
        std::shared_ptr<UserInterface> _ui;
        std::shared_ptr<AssetsRegistry> _assetsRegistry;
        std::shared_ptr<Camera> _camera;

        static JamnikEngine* Instance;
    };
   
}
