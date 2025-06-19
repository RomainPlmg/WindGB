#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Event.h"

class EventBus {
   public:
    using Listener = std::function<void(const Event&)>;

    ~EventBus();

    void Subscribe(const Listener& listener, EventCategory eventCategory);
    void Unsubscribe(const Listener& listener, EventCategory eventCategory);
    void Send(const Event& event);

   private:
    std::unordered_map<EventCategory, std::vector<Listener>> m_Listeners;
};