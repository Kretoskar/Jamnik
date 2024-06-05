#pragma once
#include <functional>
#include <map>
#include <string>
#include <vector>

class Event
{
public:
    virtual ~Event() {}
    
    virtual std::string Type() const = 0;
};

class MouseButtonEvent : public Event
{
    int button, action, mods;
    
public:
    MouseButtonEvent(int inButton, int inAction, int inMods)
        : button(inButton), action(inAction), mods(inMods) {}
    
    std::string Type() const override
    {
        char buffer[100];
        int size = sprintf_s(buffer, "MouseButton%i%i%i", button, action, mods);
        return buffer;
    }
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
