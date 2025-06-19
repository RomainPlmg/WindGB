#include "EventBus.h"

EventBus::~EventBus() { m_Listeners.clear(); }

void EventBus::Subscribe(const Listener& listener, EventCategory eventCategory) { m_Listeners[eventCategory].push_back(listener); }

void EventBus::Unsubscribe(const Listener& listener, EventCategory eventCategory) {
    auto& listeners = m_Listeners[eventCategory];

    for (auto it = listeners.begin(); it != listeners.end(); ++it) {
        if (it->target_type() == listener.target_type() && it->target<void()>() == listener.target<void>()) {
            listeners.erase(it);
            break;
        }
    }
}

void EventBus::Send(const Event& event) {
    for (const auto& [category, listeners] : m_Listeners) {
        if (event.IsInCategory(category)) {  // Checks if the event belongs to this category
            for (const auto& listener : listeners) {
                listener(event);  // Calls the listeners without copying the list
            }
        }
    }
}