#include "EventSystem.h"

void Dispatcher::Subscribe(std::string Type,  std::function<void(void*)>&& Func)
{
    _observers[Type].push_back(Func);
}

void Dispatcher::Post(std::string Type, void* Payload) const
{
    if( _observers.find(Type) == _observers.end() )
    {
        return;
    }

    auto&& observers = _observers.at( Type );

    for( auto&& observer : observers )
    {
        observer( Payload );
    }
}
