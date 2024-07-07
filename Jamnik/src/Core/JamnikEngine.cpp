#include "JamnikEngine.h"

#include <memory>

#include "AssetsRegistry.h"
#include "Logger.h"
#include "JamnikSettings.h"
#include "Window.h"


bool Jamnik::JamnikEngine::Init()
{
    // Init window
    _window = std::make_shared<Window>(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!_window->Init())
    {
        JAMNIK_LOG_ERROR("Failed to initialize window")
        return false;
    }

    // Init UI
    _ui = std::make_shared<UserInterface>();
    if (!_ui->Init(_window->GetGLFWWindow()))
    {
        JAMNIK_LOG_ERROR("Failed to create user interface")
        return false;
    }

    // Init assets
    _assetsRegistry = std::make_shared<AssetsRegistry>();
    _assetsRegistry->Init();

    // Init camera
    _camera = std::make_shared<Camera>(_window.get(), glm::vec3(1.0f, 1.0f, 1.0f));
    _camera->Init();

    // Init debug renderer
    _debugRenderer = std::make_shared<DebugRenderer>(_camera.get());
    _debugRenderer->Init();
    
    // Init renderer
    _renderer = std::make_shared<Renderer>();
    _renderer->Init(_window.get(), _camera);

    return true;
}

void Jamnik::JamnikEngine::Loop()
{
    while (!_window->GetShouldClose())
    {
        _camera->Update();
        
        _renderer->Render();
        _debugRenderer->Render();
        
        _ui->CreateFrame();
        _ui->Render();
        
        _window->Update();
    }
}

void Jamnik::JamnikEngine::Exit()
{
    _ui->Cleanup();
    _assetsRegistry->Cleanup();
    _window->ShutDown();
}
