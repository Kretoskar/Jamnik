#include "Core/Logger.h"
#include "Core/Window.h"
#include "Core/ECS/SimpleECS.h"

int main()
{
    Jamnik::Window window {1080, 720};

    ECS ecs;
    Entity a = ecs.NewEntity();
    ecs.AddComponent<Transform>(a);

    auto x = ecs.GetComponentArray<Transform>();
    for (auto &b : x->components)
    {
        b.second.position = glm::vec3(10.0f, 10.0f, 10.0f);
    }

    for (auto b : x->components)
    {
        JAMNIK_LOG_MESSAGE("val: %f", b.second.position.x);
    }
    
    if (!window.Init())
    {
        
        JAMNIK_LOG_ERROR("Failed to initialize window")
        return -1;
    }

    window.MainLoop();
    
    window.ShutDown();
    
    return 0;
}
