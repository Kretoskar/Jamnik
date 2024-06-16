#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

#define JAMNIK_BIND_EVENT(type, event) \
Dispatcher::GetInstance().Subscribe(type, \
[this](auto&& PH1) \
{ \
event(std::forward<decltype(PH1)>(PH1)); \
});

class Dispatcher
{
    Dispatcher() {}
    
public:
    Dispatcher(Dispatcher const&) = delete;
    void operator=(Dispatcher const &) = delete;
    
    static Dispatcher& GetInstance()
    {
        static Dispatcher instance;
        return instance;
    }
    
    void Subscribe(std::string Type, std::function<void(void*)>&& Func);
    
    void Post(std::string Type, void* Payload) const;

private:
    std::map<std::string, std::vector<std::function<void(void*)>>> _observers;
};

namespace MouseButtonEvent
{
    struct MouseButtonEventPayload
    {
        int button, action, mods;
    };
    
    static std::string Type(void* payload)
    {
        const int button = *reinterpret_cast<int*>(static_cast<char*>(payload));
        const int action = *reinterpret_cast<int*>(static_cast<char*>(payload) + sizeof(int));
        const int mods = *reinterpret_cast<int*>(static_cast<char*>(payload) + 2 * sizeof(int));
        
        char buffer[100];
        int size = sprintf_s(buffer, "MouseButton%i%i%i", button, action, mods);
        return buffer;
    }

    static std::string Type(int button, int action, int mods)
    {
        char buffer[100];
        int size = sprintf_s(buffer, "MouseButton%i%i%i", button, action, mods);
        return buffer;
    }
};