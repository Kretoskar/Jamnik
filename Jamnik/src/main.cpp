#include "Core/JamnikEngine.h"

int main()
{
    Jamnik::JamnikEngine jamnik;

    if (!jamnik.Init())
    {
        return -1;
    }

    jamnik.Loop();
    jamnik.Exit();

    return 0;
}
