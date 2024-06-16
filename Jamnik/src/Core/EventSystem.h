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

#define JAMNIK_POST_EVENT(type, payload) \
Dispatcher::GetInstance().Post(type, payload);

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
    static std::string Type(int button, int action, int mods)
    {
        char buffer[100];
        int size = sprintf_s(buffer, "MouseButton%i%i%i", button, action, mods);
        return buffer;
    }
};

namespace KeyboardEvent
{
    static std::string Type(int key, int action, int mods)
    {
        char buffer[100];
        int size = sprintf_s(buffer, "Key%i%i%i", key, action, mods);
        return buffer;
    }
};

namespace MousePositionEvent
{
    struct MousePositionEventPayload
    {
        int posX, posY;
    };

    static std::string Type()
    {
        return "MousePos";
    }
}