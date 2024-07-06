#include "JamnikEngine.h"

#include <memory>

#include "Logger.h"
#include "JamnikSettings.h"
#include "Window.h"


bool Jamnik::JamnikEngine::Init()
{
    // TODO: Move inits to constructors
    _window = std::make_shared<Window>(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!_window->Init())
    {
        JAMNIK_LOG_ERROR("Failed to initialize window")
        return false;
    }

    _renderer = std::make_shared<Renderer>();
    _renderer->Init(_window.get());

    return true;
}

void Jamnik::JamnikEngine::Loop()
{
    while (!_window->GetShouldClose())
    {
        _renderer->Render();
        
        _window->Update();
    }
}

void Jamnik::JamnikEngine::Exit()
{
    _renderer->Cleanup();
    _window->ShutDown();
}
