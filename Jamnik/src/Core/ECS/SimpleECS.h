#pragma once
#include <unordered_map>
#include <glm/fwd.hpp>
#include <glm/detail/type_quat.hpp>

#include "Core/JString.h"

using Entity = unsigned;
constexpr Entity MAX_ENTITIES = 100;

using ComponentType = unsigned;
constexpr ComponentType MAX_COMPONENTS = 32;

struct Transform
{
    glm::vec3 position;
    glm::quat quat;
    glm::vec3 scale;
};

class IComponentArray {};

template <typename T>
class ComponentArray : public IComponentArray
{
public:
    T* Add(Entity entity)
    {
        components[entity] = T();
        return components[entity];
    }
    
    std::unordered_map<Entity, T> components;
};

class ECS
{
public:
    template<typename T>
    void RegisterComponent()
    {
        const char* typeName = typeid(T).name();
        assert(ComponentMap.find(typeName) == ComponentMap.end() && "Registering component more than once");
        ComponentMap.insert({typeName, componentTypesCount});
        ComponentArrays.insert({componentTypesCount, ComponentArray<T>()});
        componentTypesCount++;
    }

    template<typename T>
    void AddComponent(Entity entity)
    {
        const char* typeName = typeid(T).name();
        if (ComponentMap.find(typeName) == ComponentMap.end())
        {
            RegisterComponent<T>();
        }

        Entities[entity][ComponentMap[typeName]] = GetComponentArray<T>()->Add(entity);
    }

    template<typename T>
    bool HasComponent(Entity entity)
    {
        const char* typeName = typeid(T).name();
        if (ComponentMap.find(typeName) == ComponentMap.end())
        {
            JAMNIK_LOG_ERROR("Looking for non existent component")
            return false;
        }

        return Entities[entity][ComponentMap[typeName]];
    }
    
    static Entity NewEntity();
    
private:
    template<typename T>
    ComponentArray<T>* GetComponentArray()
    {
        const char* typeName = typeid(T).name();
        if (ComponentMap.find(typeName) == ComponentMap.end())
        {
            JAMNIK_LOG_ERROR("Trying to find non existent component array")
            return nullptr;
        }

        return std::static_pointer_cast<ComponentArray<T>>(ComponentArrays[ComponentMap[typeName]]);
    }
    
    static Entity EntityCount;
    static void* Entities[MAX_ENTITIES][MAX_COMPONENTS];

    std::unordered_map<ComponentType, IComponentArray> ComponentArrays;
    std::unordered_map<const char*, ComponentType> ComponentMap;
    
    ComponentType componentTypesCount = 0;
};