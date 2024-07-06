#include "JamnikEngine.h"

#include <memory>

#include "Logger.h"
#include "JamnikSettings.h"
#include "Window.h"


bool Jamnik::JamnikEngine::Init()
{
    window = std::make_shared<Window>(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!window->Init())
    {
        JAMNIK_LOG_ERROR("Failed to initialize window")
        return false;
    }
}

void Jamnik::JamnikEngine::Loop()
{
    while (!window->GetShouldClose())
    {
        window->MainLoop();
    }
}

void Jamnik::JamnikEngine::Exit()
{
    window->ShutDown();
}
