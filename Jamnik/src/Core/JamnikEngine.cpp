#include "JamnikEngine.h"

#include <memory>

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
    
    // Init renderer
    _renderer = std::make_shared<Renderer>();
    _renderer->Init(_window.get());

    return true;
}

void Jamnik::JamnikEngine::Loop()
{
    while (!_window->GetShouldClose())
    {
        _renderer->Render();
        _ui->CreateFrame();
        _ui->Render();
        _window->Update();
    }
}

void Jamnik::JamnikEngine::Exit()
{
    _ui->Cleanup();
    _renderer->Cleanup();
    _window->ShutDown();
}
