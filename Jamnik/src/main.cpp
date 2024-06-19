#include "Core/Logger.h"
#include "Core/Window.h"
#include "Core/JString.h"

int main()
{
    Jamnik::Window window {1080, 720};

    JString j("aSD");
    JString X("aSD");

    JString q ("qw1");

    char buffer[100];
    sprintf_s(buffer, "qw%d", 1);

    //std::cout << buffer;
    JString d (buffer);
    
    
    if (!window.Init())
    {
        
        JAMNIK_LOG_ERROR("Failed to initialize window")
        return -1;
    }

    window.MainLoop();
    
    window.ShutDown();
    
    return 0;
}
