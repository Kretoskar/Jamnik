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

class Event
{
public:
    virtual ~Event() = default;
    
private:
    virtual std::string Type() const = 0;

    friend class Dispatcher;
};

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
    
    void Subscribe(std::string Type, std::function<void(const Event&)>&& Slot)
    {
        _observers[Type].push_back(Slot);
    }
    
    void Post(const Event& Event) const
    {
        const auto type = Event.Type();

        // Ignore events for which we do not have an observer (yet).
        if( _observers.find( type ) == _observers.end() )
        {
            return;
        }

        auto&& observers = _observers.at( type );

        for( auto&& observer : observers )
        {
            observer( Event );
        }
    }

private:
    std::map<std::string, std::vector<std::function<void(const Event&)>>> _observers;
};

class MouseButtonEvent : public Event
{
    int button, action, mods;
    
public:
    MouseButtonEvent(int inButton, int inAction, int inMods)
        : button(inButton), action(inAction), mods(inMods) {}

    MouseButtonEvent(int inButton, int inAction)
        : button(inButton), action(inAction), mods(0) {}

    static std::string Type(int button, int action, int mods)
    {
        char buffer[100];
        int size = sprintf_s(buffer, "MouseButton%i%i%i", button, action, mods);
        return buffer;
    }

    static std::string Type(int button, int action)
    {
        return Type(button, action, 0);
    }


    int GetButton() const { return button; }
    int GetAction() const { return action; }
    int GetMods() const { return mods; }

private:
    std::string Type() const override
    {
        return MouseButtonEvent::Type(button, action, mods);
    }
};

class KeyboardEvent : public Event
{
    int key, action, mods;

public:
    KeyboardEvent(int inKey, int inAction, int inMods)
        : key(inKey), action(inAction), mods(inMods) {}

    KeyboardEvent(int inKey, int inAction)
        : key(inKey), action(inAction), mods(0) {}
    
    static std::string Type(int key, int action, int mods)
    {
        char buffer[100];
        int size = sprintf_s(buffer, "Key%i%i%i", key, action, mods);
        return buffer;
    }

    static std::string Type(int key, int action)
    {
        return Type(key, action, 0);
    }

    int GetKey() const { return key; }
    int GetAction() const { return action; }
    int GetMods() const { return mods; }

private:
    std::string Type() const override
    {
        return KeyboardEvent::Type(key, action, mods);
    }
};