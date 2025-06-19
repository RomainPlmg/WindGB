#pragma once

#include "Event.h"

class EventApp : public Event {
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApp);
};

class DMATransfertEvent final : public EventApp {
   public:
    DMATransfertEvent(u16 sourceAddr): m_SourceAddr(sourceAddr) {}

    EVENT_CLASS_TYPE(EventType::DMATransfert);

    std::string ToString() const override {
        std::stringstream ss;
        ss << "DMA -> OAM transfert";
        return ss.str();
    }

    u16 m_SourceAddr;
};

class QuitEvent final : public EventApp {
   public:
    QuitEvent() = default;

    EVENT_CLASS_TYPE(EventType::Quit);

    std::string ToString() const override {
        std::stringstream ss;
        ss << "Quit";
        return ss.str();
    }
};