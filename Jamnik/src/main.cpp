#include "Core/Logger.h"
#include "Core/Window.h"

int main()
{
    Jamnik::Window window {};
    
    if (!window.Init())
    {
        LOG_ERROR("Failed to initialize window")
        return -1;
    }

    window.MainLoop();
    window.ShutDown();
    
    return 0;
}
