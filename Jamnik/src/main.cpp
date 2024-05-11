#include "Core/Application.h"

int main()
{
    Jamnik::Application application;
    
    if (application.Init())
    {
        while (!application.GetShouldClose())
        {
            application.Update();
        }    
    }
    
    application.ShutDown();
    
    return 0;
}