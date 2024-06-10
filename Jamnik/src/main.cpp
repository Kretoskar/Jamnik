#include "Core/Logger.h"
#include "Core/Window.h"

int main()
{
    Jamnik::Window window {1080, 720};
    
    if (!window.Init())
    {
        JAMNIK_LOG_ERROR("Failed to initialize window")
        return -1;
    }

    window.MainLoop();
    window.ShutDown();
    
    return 0;
}
