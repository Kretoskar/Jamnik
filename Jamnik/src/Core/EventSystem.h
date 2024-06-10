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
    
    void Subscribe(std::string Type, std::function<void(const Event&)>&& Slot);
    
    void Post(const Event& Event) const;

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

    static std::string StaticType(int button, int action, int mods);

    static std::string StaticType(int button, int action);


    int GetButton() const { return button; }
    int GetAction() const { return action; }
    int GetMods() const { return mods; }

private:
    std::string Type() const override;
};

class KeyboardEvent : public Event
{
    int key, action, mods;

public:
    KeyboardEvent(int inKey, int inAction, int inMods)
        : key(inKey), action(inAction), mods(inMods) {}

    KeyboardEvent(int inKey, int inAction)
        : key(inKey), action(inAction), mods(0) {}
    
    static std::string StaticType(int key, int action, int mods);

    static std::string StaticType(int key, int action);

    int GetKey() const { return key; }
    int GetAction() const { return action; }
    int GetMods() const { return mods; }

private:
    std::string Type() const override;
};

class MousePositionEvent : public Event
{
    double posX, posY;

public:
    MousePositionEvent(double posX, double posY)
        : posX(posX), posY(posY) {}
    
    static std::string StaticType()
    {
        return "MousePos";
    }

    double GetPosX() const { return posX; }
    double GetPosY() const { return posY; }

private:
    std::string Type() const override;
};