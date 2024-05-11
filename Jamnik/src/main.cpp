#include "Core/Application.h"

int main()
{
    Application application;
    
    if (application.Start())
    {
        while (!application.GetShouldClose())
        {
            application.Update();
        }    
    }
    
    application.ShutDown();
    
    return 0;
}