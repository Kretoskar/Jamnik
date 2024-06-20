#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "JString.h"

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
    
    void Subscribe(JString Type, std::function<void(void*)>&& Func);
    
    void Post(JString Type, void* Payload) const;

private:
    std::map<JString, std::vector<std::function<void(void*)>>> _observers;
};

namespace MouseButtonEvent
{
    static JString Type(int button, int action, int mods)
    {
        static std::map<unsigned, JString> lookupMap;

        const unsigned lookupKey = button * 100 + action * 10 + mods;
        if (lookupMap.count(lookupKey) == 0)
        {
            char buffer[100];
            int size = sprintf_s(buffer, "MouseButton%i%i%i", button, action, mods);
            lookupMap[lookupKey] = buffer;
        }
        

        return lookupMap[lookupKey];
    }
};

namespace KeyboardEvent
{
    static JString Type(int key, int action, int mods)
    {
        static std::map<unsigned, JString> lookupMap;
        
        const unsigned lookupKey = key * 100 + action * 10 + mods;
        if (lookupMap.count(lookupKey) == 0)
        {
            char buffer[100];
            int size = sprintf_s(buffer, "Key%i%i%i", key, action, mods);
            lookupMap[lookupKey] = buffer;
        }
        

        return lookupMap[lookupKey];
    }
};

namespace MousePositionEvent
{
    struct MousePositionEventPayload
    {
        int posX, posY;
    };

    static JString Type()
    {
        static JString type = JString("MousePos");
        return type;
    }
}