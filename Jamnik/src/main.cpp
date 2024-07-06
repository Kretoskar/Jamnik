#include "Core/JamnikEngine.h"

int main()
{
    if (!Jamnik::JamnikEngine::GetInstance().Init())
    {
        return -1;
    }

    Jamnik::JamnikEngine::GetInstance().Loop();
    Jamnik::JamnikEngine::GetInstance().Exit();

    return 0;
}
