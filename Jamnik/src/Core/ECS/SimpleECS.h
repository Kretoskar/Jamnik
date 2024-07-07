#pragma once
#include <unordered_map>
#include <glm/fwd.hpp>
#include <glm/detail/type_quat.hpp>

#include "Core/JString.h"

using Entity = unsigned;
constexpr Entity MAX_ENTITIES = 100;

using ComponentType = unsigned;
constexpr ComponentType MAX_COMPONENTS = 32;

class IComponentArray {};

template <typename T>
class ComponentArray : public IComponentArray
{
public:
    T* Add(Entity entity)
    {
        components[entity] = T();
        return &components[entity];
    }
    
    std::unordered_map<Entity, T> components;
};

class ECS
{
    ECS() {}
    
    ECS(ECS const&) = delete;
    void operator=(ECS const &) = delete;
    
    static ECS& GetInstance()
    {
        static ECS instance;
        return instance;
    }
    
public:
    template<typename T>
    static void RegisterComponent()
    {
        const char* typeName = typeid(T).name();
        assert(GetInstance().ComponentMap.find(typeName) == GetInstance().ComponentMap.end() && "Registering component more than once");
        GetInstance().ComponentMap.insert({typeName, GetInstance().componentTypesCount});
        GetInstance().ComponentArrays.insert({GetInstance().componentTypesCount, std::make_shared<ComponentArray<T>>()});
        GetInstance().componentTypesCount++;
    }

    template<typename T>
    static T* AddComponent(Entity entity)
    {
        const char* typeName = typeid(T).name();
        if (GetInstance().ComponentMap.find(typeName) == GetInstance().ComponentMap.end())
        {
            RegisterComponent<T>();
        }

        GetInstance().Entities[entity][GetInstance().ComponentMap[typeName]] = GetComponentArray<T>()->Add(entity);
        return static_cast<T*>(GetInstance().Entities[entity][GetInstance().ComponentMap[typeName]]);
    }

    template<typename T>
    static bool HasComponent(Entity entity)
    {
        const char* typeName = typeid(T).name();
        if (GetInstance().ComponentMap.find(typeName) == GetInstance().ComponentMap.end())
        {
            JAMNIK_LOG_ERROR("Looking for non existent component")
            return false;
        }

        return GetInstance().Entities[entity][GetInstance().ComponentMap[typeName]];
    }

    template<typename T>
    static T* GetComponent(Entity entity)
    {
        const char* typeName = typeid(T).name();
        if (GetInstance().ComponentMap.find(typeName) == GetInstance().ComponentMap.end())
        {
            JAMNIK_LOG_ERROR("Looking for non existent component")
            return nullptr;
        }

        return static_cast<T*>(GetInstance().Entities[entity][GetInstance().ComponentMap[typeName]]);
    }
    
    static Entity NewEntity()
    {
        static Entity EntityCount = 0;
        
        if (EntityCount >= MAX_ENTITIES)
        {
            JAMNIK_LOG_ERROR("Reached maximum number of entities. Expect unexpected behaviour :)")
            return MAX_ENTITIES;
        }

        EntityCount++;
        return EntityCount - 1;
    }

    template<typename T>
    static std:: shared_ptr<ComponentArray<T>> GetComponentArray()
    {
        const char* typeName = typeid(T).name();
        if (GetInstance().ComponentMap.find(typeName) == GetInstance().ComponentMap.end())
        {
            JAMNIK_LOG_ERROR("Trying to find non existent component array")
            return nullptr;
        }

        return std::static_pointer_cast<ComponentArray<T>>(GetInstance().ComponentArrays[GetInstance().ComponentMap[typeName]]);
    }
    
private:
    void* Entities[MAX_ENTITIES][MAX_COMPONENTS];

    std::unordered_map<ComponentType, std::shared_ptr<IComponentArray>> ComponentArrays;
    std::unordered_map<const char*, ComponentType> ComponentMap;
    
    ComponentType componentTypesCount = 0;
};