#include "EventSystem.h"

void Dispatcher::Subscribe(std::string Type, std::function<void(const Event&)>&& Slot)
{
    _observers[Type].push_back(Slot);
}

void Dispatcher::Post(const Event& Event) const
{
    const std::string type = Event.Type();
    
    if( _observers.find(type) == _observers.end() )
    {
        return;
    }

    auto&& observers = _observers.at( type );

    for( auto&& observer : observers )
    {
        observer( Event );
    }
}

std::string MouseButtonEvent::StaticType(int button, int action, int mods)
{
    char buffer[100];
    int size = sprintf_s(buffer, "MouseButton%i%i%i", button, action, mods);
    return buffer;
}

std::string MouseButtonEvent::StaticType(int button, int action)
{
    return StaticType(button, action, 0);
}

std::string MouseButtonEvent::Type() const
{
    return MouseButtonEvent::StaticType(button, action, mods);
}

std::string KeyboardEvent::StaticType(int key, int action, int mods)
{
    char buffer[100];
    int size = sprintf_s(buffer, "Key%i%i%i", key, action, mods);
    return buffer;
}

std::string KeyboardEvent::StaticType(int key, int action)
{
    return StaticType(key, action, 0);
}

std::string MousePositionEvent::Type() const
{
    return StaticType();
}

std::string KeyboardEvent::Type() const
{
    return KeyboardEvent::StaticType(key, action, mods);
}
