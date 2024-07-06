#include "SimpleECS.h"

#include "Core/Logger.h"

Entity ECS::EntityCount = 0;

Entity ECS::NewEntity()
{
    if (EntityCount >= MAX_ENTITIES)
    {
        JAMNIK_LOG_ERROR("Reached maximum number of entities. Expect unexpected behaviour :)")
        return MAX_ENTITIES;
    }

    EntityCount++;
    return EntityCount - 1;
}
