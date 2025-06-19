#pragma once

#include <sstream>
#include <string>

enum class EventType {
    None = 0,

    /* App events */
    DMATransfert,
    Quit
};

enum EventCategory { EventCategoryNone = 0, EventCategoryApp = 1 << 0 };

#define EVENT_CLASS_TYPE(type)                                  \
    virtual EventType GetType() const override { return type; } \
    virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int GetCategoryFlags() const override { return category; }

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

/* Pure virtual class, will be inherited by all the sub event classes */
class Event {
   public:
    Event() = default;
    virtual ~Event() = default;

    /* Getters */
    virtual int GetCategoryFlags() const = 0;
    virtual EventType GetType() const = 0;
    virtual const char* GetName() const = 0;
    inline bool IsInCategory(const EventCategory& category) const { return (GetCategoryFlags() & category); }

    virtual std::string ToString() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString(); }
};